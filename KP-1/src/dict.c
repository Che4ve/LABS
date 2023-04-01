#include "../headers/dict.h"

//typedef unsigned int uint;

uint hash(const char* key)
{
    uint value = 0;
    uint key_len = strlen(key);

    for (uint i = 0; i < key_len; i++) {
        value = value * 33 + key[i];
    }

    return value % TABLE_SIZE;
}

