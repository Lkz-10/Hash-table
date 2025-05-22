#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int ARGC     = 3;
const int NBUCKETS = 14363;

typedef unsigned int (*hash_func_ptr_t)(const char* key, int length);

enum err_codes
{
    ERROR = -1,
    OK    = 0
};

enum hash_funcs
{
    HASH_LENGTH     = 1,
    HASH_ASCII      = 2,
    HASH_POS        = 3,
    HASH_DJB2       = 4,
    HASH_CRC32      = 5
};

enum table_contents
{
    PRESENCE = 1,
    ABSENCE  = 0
};

enum text_handling_modes
{
    FILLING  = 1,
    CHECKING = 2
};

struct node_t
{
    node_t* next;
    char*   word;
};

struct hash_table_t
{
    node_t**        buckets;
    hash_func_ptr_t func;
};

struct stats_t
{
    int words_in;
    int words_out;
};

#endif
