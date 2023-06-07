#ifndef __DICT_H__
#define __DICT_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/globals.h"

typedef unsigned int uint;

typedef struct _hash_node {
    void* value;
    struct _hash_node* next_node;
} HashNode;

typedef struct _hash_table {
    uint size;
    HashNode** table;
} HashTable;

HashTable* createTable(int table_size);

HashNode* newNode(void* value_p);

void* get_value(HashNode* node);

HashNode* ht_get_next(HashNode* node);

HashNode* ht_get_last(HashNode* node);

uint hash(HashTable* ht, const char* key);

void ht_insert(HashTable* ht, const char* key, void* pointer);

HashNode* ht_get_first(HashTable* ht, const char* key);

HashNode* ht_get_next(HashNode* node);

void ht_free(HashTable* ht);

#endif