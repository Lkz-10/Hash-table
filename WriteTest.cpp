#include <stdio.h>
#include <stdlib.h>

const char* word        = "Leo";
const char* file_name   = "text.txt";

const int NTIMES = 10000;

int main()
{
    FILE* file_ptr = fopen(file_name, "w");

    for (int i = 0; i < NTIMES; ++i)
    {
        fprintf(file_ptr, "%s ", word);
    }

    fclose(file_ptr);

    return 0;
}
