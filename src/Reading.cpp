#include "../include/Globals.h"

int TextToBuckets(const char* file_name, node_t** buckets)
{
    if (!file_name || !buckets)
    {
        fprintf(stderr, "TextToBuckets() arguments error: file_name = %s, buckets = %p\n",
                        file_name, buckets);
        return ERROR;
    }

    FILE* file_ptr = fopen(file_name, "rb");

    if (!file_ptr)
    {
        fprintf(stderr, "TextToBuckets() error: cannot open \"%s\"\n", file_name);
        return ERROR;
    }

    fseek(file_ptr, 0, SEEK_END);
    size_t file_size = ftell(file_ptr);
    rewind(file_ptr);

    char* text = (char*) calloc(file_size, sizeof(char));

    if (!text)
    {
        fprintf(stderr, "TextToBuckets() error: unable to calloc memory for text"
                        "(length = %lld)\n", file_size);
        fclose(file_ptr);
        return ERROR;
    }

    if (fread(text, sizeof(char), file_size, file_ptr) != file_size)
    {
        fprintf(stderr, "TextToBuckets() error: fread() returned wrong value\n");

        fclose(file_ptr);
        free(text);
        return ERROR;
    }

    fclose(file_ptr);


}

int FillBuckets(const char* text, node_t** buckets)
{
    if (!text || !buckets)
    {
        fprintf(stderr, "FillBuckets() arguments error: text = %p, buckets = %p\n",
                        text, buckets);
        return ERROR;
    }


}
