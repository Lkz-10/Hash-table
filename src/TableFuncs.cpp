#include "../include/TableFuncs.h"
#include "../include/HashFuncs.h"

int HashTableCtor(hash_table_t* hash_table, enum hash_funcs func_name)
{
    if (!hash_table)
    {
        fprintf(stderr, "HashTableCtor() error: hash_table is NULL-pointer\n");
        return ERROR;
    }

    hash_table->buckets = (node_t**) calloc(NBUCKETS, sizeof(node_t*));

    if (!hash_table->buckets)
    {
        fprintf(stderr, "HashTableCtor() error: cannot calloc memory\n");
        return ERROR;
    }

    hash_table->func = FunctionPtr(func_name);

    if (hash_table->func == NULL)
    {
        free(hash_table->buckets);
        return ERROR;
    }

    return OK;
}

hash_func_ptr_t FunctionPtr(enum hash_funcs name)
{
    switch (name)
    {
        case HASH_LENGTH:       return HashLength;
        case HASH_ASCII:        return HashASCII;
        case HASH_POS:          return HashPos;
        case HASH_DJB2:         return HashDJB2;
        case HASH_CRC32:        return HashCRC32;
        case HASH_CRC32_SSE:    return __CRC32;
        // case HASH_CRC32_ASM:    return CRC32_ASM;

        default:
            fprintf(stderr, "Unknown hash function: %d\n", name);
            return NULL;
    }
}

node_t* CreateNode(char* word, const int length)
{
    if (!word)
    {
        fprintf(stderr, "CreateNode() error: no word given\n");
        return NULL;
    }

    node_t* new_node = (node_t*) calloc(1, sizeof(node_t));

    if (!new_node)
    {
        fprintf(stderr, "CreateNode() error: unable to calloc memory for new_node\n");
        return NULL;
    }

    new_node->word = (char*) calloc(length, sizeof(char));

    if (!(new_node->word))
    {
        fprintf(stderr, "CreateNode() error: unable to calloc memory for the word"
                        "(length = %d)\n", length);
        return NULL;
    }

    strncpy(new_node->word, word, length);

    new_node->next = NULL;

    return new_node;
}

int TableDtor(hash_table_t* table)
{
    for (int i = 0; i < NBUCKETS; ++i)
    {
        ListDtor(table->buckets[i]);
        table->buckets[i] = NULL;
    }

    free(table->buckets);
    table->buckets = NULL;

    table->func = NULL;

    return OK;
}

int ListDtor(node_t* node)
{
    if (!node) return OK;

    ListDtor(node->next);

    free(node->word);
    node->word = NULL;

    free(node);
    node = NULL;

    return OK;
}

int IsInTable(char* word, node_t* node)
{
    if (!word)
    {
        fprintf(stderr, "IsInTable() argumments error: word = %p\n", word);
        return ERROR;
    }

    while (node)
    {
        // if (NewStrcmp(word, node->word) == 0) return PRESENCE;
        if (strcmp(word, node->word) == 0) return PRESENCE;
        node = node->next;
    }

    return ABSENCE;
}

int NewStrcmp(const char* str1, const char* str2)
{
    __m256i string1 = _mm256_loadu_si256((const __m256i*)(str1));
    __m256i string2 = _mm256_loadu_si256((const __m256i*)(str2));

    return ~(_mm256_movemask_epi8(_mm256_cmpeq_epi8(string1, string2)));
}

int GetData(hash_table_t* table, const char* file_name)
{
    if (!table || !file_name)
    {
        fprintf(stderr, "GetData() error: table = %p, file_name = %p\n", table, file_name);
        return ERROR;
    }

    FILE* file_ptr = fopen(file_name, "w");

    if (!file_ptr)
    {
        fprintf(stderr, "GetData() error: cannot open file \"%s\"\n", file_name);
        return ERROR;
    }

    for (int i = 0; i < NBUCKETS; ++i)
    {
        node_t* curr = table->buckets[i];

        int nnodes = 0;

        while (curr)
        {
            nnodes++;
            curr = curr->next;
        }

        fprintf(file_ptr, "%d, %d\n", i, nnodes);
    }

    fclose(file_ptr);

    return OK;
}

int Dump(node_t** buckets, const char* file_name)
{
    if (!buckets || !file_name)
    {
        fprintf(stderr, "Dump() error: buckets = %p, file_name = %p\n", buckets, file_name);
        return ERROR;
    }

    FILE* file_ptr = fopen(file_name, "w");

    if (!file_ptr)
    {
        fprintf(stderr, "Dump() error: cannot open \"%s\"\n", file_name);
        return ERROR;
    }

    fprintf(file_ptr, "digraph G\n{\n   rankdir=UD;\n");
    fprintf(file_ptr, "    node [shape=record];\n");
    fprintf(file_ptr, "    rankdir=HT;\n");
    fprintf(file_ptr, "    splines=false;\n");
    fprintf(file_ptr, "    HashTable [style=filled, fillcolor=plum1, height=0.8, width=%d.0 label=\"", NBUCKETS);

    for (int i = 0; i < NBUCKETS; ++i)
    {
        fprintf(file_ptr, "<f%d> %d ", i, i);

        if (i < NBUCKETS - 1) fprintf(file_ptr, "| ");
    }

    fprintf (file_ptr, "\", color=purple];\n");

    for (int i = 0; i < NBUCKETS; ++i)
    {
        node_t* curr     = buckets[i];
        int     node_num = 0;

        while (curr)
        {
            fprintf(file_ptr, "    node%d_%d[style = filled, fillcolor = lightcyan, label = \"%s\", color = blue];\n",
                    i, node_num, curr->word);

            if (node_num > 0) fprintf(file_ptr, "    node%d_%d->node%d_%d;\n", i, node_num - 1, i, node_num);

            curr = curr->next;
            node_num++;
        }

        if (buckets[i]) fprintf(file_ptr, "    HashTable:f%d->node%d_0;\n", i, i);
    }

    fprintf(file_ptr, "}\n");

    fclose(file_ptr);

    return OK;
}


int ArgcCheck(const int argc)
{
    if (argc != ARGC)
    {
        fprintf(stderr, "Wrong number of arguments for main() - %d (need %d)\n", argc, ARGC);
        return ERROR;
    }

    return OK;
}
