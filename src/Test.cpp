#include "../include/Test.h"

int Test(const char* file_name, hash_table_t* table, stats_t* stats)
{
    if (!file_name || !table)
    {
        fprintf(stderr, "Test() arguments error: file_name = %p, table = %p\n", file_name, table);
        return ERROR;
    }

    char*  text      = NULL;
    size_t text_size = 0;

    if (CreateBuffer(file_name, &text, &text_size) != OK) return ERROR;

    if (HandleText(text, text_size, table, CHECKING, stats) != OK)
    {
        free(text);
        TableDtor(table);

        return ERROR;
    }

    free(text);

    return OK;
}
