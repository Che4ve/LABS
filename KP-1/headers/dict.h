#ifndef __DICT_H__
#define __DICT_H__

#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE 200

typedef unsigned int uint;

typedef struct _elem {
    char* key;
    int value;
} Elem;

uint hash(const char* key);


#endif