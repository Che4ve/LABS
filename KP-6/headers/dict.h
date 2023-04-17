#ifndef __DICT_H__
#define __DICT_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/globals.h"

#define TABLE_SIZE 1051

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

void ht_free(HashTable* ht);

void* get_value(HashNode* node);

HashNode* get_next(HashNode* node);

HashNode* get_last(HashNode* node);

uint hash(HashTable* ht, const char* key);

void ht_insert(HashTable* ht, const char* key, void* pointer);

void* ht_find(HashTable* ht, char* key);

HashNode* ht_get_first(HashTable* ht, const char* key);

HashNode* ht_get_next(HashNode* node);

void ht_print(HashTable* ht);

typedef struct _studentpc StudentPC;
void ht_print_specs(StudentPC* pc);

#endif