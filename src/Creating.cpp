#include "../include/Creating.h"
#include "../include/HashFuncs.h"

int CreateBuffer(const char* file_name, char** text, size_t* file_size)
{
    if (!file_name)
    {
        fprintf(stderr, "CreateBuffer() error: file_name = NULL\n");
        return ERROR;
    }

    FILE* file_ptr = fopen(file_name, "rb");

    if (!file_ptr)
    {
        fprintf(stderr, "CreateBuffer() error: cannot open \"%s\"\n", file_name);
        return ERROR;
    }

    fseek(file_ptr, 0, SEEK_END);
    *file_size = ftell(file_ptr);
    rewind(file_ptr);

    *text = (char*) calloc(*file_size + 1, sizeof(char));

    if (!(*text))
    {
        fprintf(stderr, "CreateBuffer() error: unable to calloc memory for text"
                        "(length = %ld)\n", *file_size);
        fclose(file_ptr);
        return ERROR;
    }

    if (fread(*text, sizeof(char), *file_size, file_ptr) != *file_size)
    {
        fprintf(stderr, "CreateBuffer() error: fread() returned wrong value\n");

        fclose(file_ptr);
        free(*text);
        return ERROR;
    }

    fclose(file_ptr);

    return OK;
}

int HandleText(char* text, size_t text_size, hash_table_t* table, int mode, stats_t* stats)
{
    if (!text || !table)
    {
        fprintf(stderr, "FillBuckets() arguments error: text = %p, table = %p\n",
                        text, table);
        return ERROR;
    }

    char* curr = text;

    while (curr < text + text_size)
    {
        // fprintf(stderr, "curr = %p, max = %p\n", curr, text + text_size);

        while (curr < text + text_size && !isalpha(*curr)) curr++;

        int word_len = 0;
        while (curr < text + text_size && isalpha(*curr))
        {
            word_len++;
            curr++;
        }

        if (word_len > 0)
        {
            *curr  = '\0';
             curr -= word_len;

            // int bucket_number = table->func(curr, word_len) % NBUCKETS;
            int bucket_number = __CRC32(curr, word_len) % NBUCKETS;

            int checking_result = IsInTable(curr, table->buckets[bucket_number]);

            if (checking_result == ERROR) return ERROR;

            if (mode == FILLING && checking_result == ABSENCE)
            {
                node_t* node                    = CreateNode(curr, word_len);
                node->next                      = table->buckets[bucket_number];
                table->buckets[bucket_number]   = node;
            }

            if (mode == CHECKING)
            {
                (checking_result == PRESENCE) ? stats->words_in++ : stats->words_out++;
            }

            curr += word_len;
        }
    }

    return OK;
}
