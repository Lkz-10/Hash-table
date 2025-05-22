#ifndef __CREATING_H__
#define __CREATING_H__

#include <ctype.h>

#include "../include/TableFuncs.h"

int CreateBuffer    (const char* file_name, char** text, size_t* file_size);
int HandleText      (char* text, size_t text_size, hash_table_t* table, int mode, stats_t* stats);

#endif
