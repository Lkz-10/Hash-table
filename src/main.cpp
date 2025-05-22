#include "../include/Creating.h"
#include "../include/Test.h"
#include <time.h>

#define FUNC_NAME HASH_CRC32

int main(const int argc, const char** argv)
{
    if (ArgcCheck(argc) != OK) return ERROR;

    hash_table_t hash_table = {};

    if (HashTableCtor(&hash_table, FUNC_NAME) != OK) return ERROR;

    char*   text      = NULL;
    size_t  text_size = 0;

    if (CreateBuffer(argv[1], &text, &text_size) != OK) return ERROR;

    if (HandleText(text, text_size, &hash_table, FILLING, NULL) != OK)
    {
        free(text);
        TableDtor(&hash_table);

        return ERROR;
    }

    free(text);

    long int nwords = 0, busy = 0, free = 0;

    for (int i = 0; i < NBUCKETS; ++i)
    {
        node_t* curr = hash_table.buckets[i];

        if (curr) busy++;
        else free++;

        while (curr)
        {
            curr = curr->next;
            nwords++;
        }
    }

    printf("Nwords = %ld\nbuckets: buisy - %ld, free - %ld\n", nwords, busy, free);

    stats_t stats = {};

    if (Test(argv[2], &hash_table, &stats) != OK) return ERROR;

    printf("Checking result: the text contains %d words, does not contain %d words\n",
           stats.words_in, stats.words_out);

    int max_coll_size = 0;

    for (int i = 0; i < NBUCKETS; ++i)
    {
        node_t* curr = hash_table.buckets[i]; int elems = 0;

        while (curr)
        {
            elems++;
            curr = curr->next;
        }

        if (elems > max_coll_size) max_coll_size = elems;
    }

    fprintf(stderr, "Max collision size - %d\n", max_coll_size);

    // if (GetData(&hash_table, argv[3]) != OK) return ERROR;

    // if (Dump(hash_table.buckets, argv[2]) != OK)
    // {
    //     TableDtor(&hash_table);
    //     return ERROR;
    // }

    if (TableDtor(&hash_table) != OK) return ERROR;

    return OK;
}
