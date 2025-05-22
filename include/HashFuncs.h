#ifndef __HASH_FUNCS_H__
#define __HASH_FUNCS_H__

#include <stdint.h>
#include <nmmintrin.h>
#include <string.h>
#include <stdio.h>

#include "Globals.h"

extern "C" uint32_t CRC32_ASM(const char* key, int length);

uint32_t    HashLength      (const char* key, int length);
uint32_t    HashASCII       (const char* key, int length);
uint32_t    HashPos         (const char* key, int length);
uint32_t    HashDJB2        (const char* key, int length);
uint32_t    HashCRC32       (const char* key, int length);
uint32_t    __CRC32         (const char* key, int length);

int         CRC32TableCtor  ();

#endif
