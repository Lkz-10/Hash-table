#include "../include/HashFuncs.h"

uint32_t HashLength(const char* key, int length)
{
    return (uint32_t) length;
}

uint32_t HashASCII(const char* key, int length)
{
    uint32_t hash = 0;

    for (int i = 0; i < length; ++i)
    {
        hash += key[i];
    }

    return hash;
}

uint32_t HashPos(const char* key, int length)
{
    uint32_t hash = 0;

    for (int i = 0; i < length; ++i)
    {
        hash += key[i] * (i + 1);
    }

    return hash;

}

uint32_t HashDJB2(const char* key, int length)
{
    uint32_t hash = 5381;

    for (int i = 0; i < length; ++i)
    {
        hash = (hash << 5) + hash + (uint32_t) key[i];
    }

    return hash;
}

static uint32_t crc_table[256] = {};

int CRC32TableCtor()
{
    uint32_t constant = 0x82F63B78;

    for (uint32_t i = 0; i < 256; i++)
    {
        uint32_t crc = i;

        for (int j = 0; j < 8; j++)
        {
            crc = (crc >> 1) ^ ((crc & 1) ? constant : 0);
        }

        crc_table[i] = crc;
    }

    return OK;
}

uint32_t HashCRC32(const char* key, int length)
{
    if (!crc_table[1]) CRC32TableCtor();

    uint32_t hash = 0xFFFFFFFF;

    for (int i = 0; i < length; i++)
    {
        hash = (hash >> 8) ^ crc_table[(hash ^ key[i]) & 0xFF];
    }

    hash ^= 0xFFFFFFFF;

    return hash;
}

uint32_t __CRC32(const char* key, int length)
{
    const uint8_t* key8 = (const uint8_t*) key;

    uint32_t crc = 0xFFFFFFFF;

    while (length && ((uintptr_t) key8 & 7))
    {
        crc = _mm_crc32_u8(crc, *key8);

        key8++;
        length--;
    }

    const uint64_t* key64 = (const uint64_t*) key8;

    while (length >= 8)
    {
        crc = (uint32_t) _mm_crc32_u64(crc, *key64);

        key64++;
        length -= 8;
    }

    key8 = (const uint8_t*) key64;

    while (length--)
    {
        crc = _mm_crc32_u8(crc, *key8);
        key8++;
    }

    return crc ^ 0xFFFFFFFF;
}
