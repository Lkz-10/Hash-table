#ifndef __LIST_FUNCS_H__
#define __LIST_FUNCS_H__

#include <immintrin.h>

#include "../include/Globals.h"

int             HashTableCtor   (hash_table_t* hash_table, enum hash_funcs func_name);
hash_func_ptr_t FunctionPtr     (enum hash_funcs name);
node_t*         CreateNode      (char* word, const int length);
int             ListDtor        (node_t* node);
int             TableDtor       (hash_table_t* table);
int             IsInTable       (char* word, node_t* node);
int             NewStrcmp       (const char* str1, const char* str2);
int             GetData         (hash_table_t* table, const char* file_name);
int             Dump            (node_t** buckets, const char* file_name);

#endif
