#include "../headers/dict.h"

//typedef unsigned int uint;

HashTable* createTable(int table_size)
{
    HashTable* new_ht = malloc(sizeof(HashTable));
    if (new_ht == NULL) return NULL;
    new_ht->table = calloc(table_size, sizeof(HashNode));
    new_ht->size = table_size;
    return new_ht;
}

HashNode* newNode(void* value_p)
{
    HashNode* new_node = malloc(sizeof(HashNode));
    if (new_node == NULL) return NULL;
    new_node->value = value_p;
    new_node->next_node = NULL;
    return new_node;
}

void* get_value(HashNode* node)
{
    if (node == NULL) {
        return NULL;
    }
    return node->value;
}

HashNode* get_next(HashNode* node)
{
    if (node == NULL) {
        return NULL;
    }
    return node->next_node;
}

HashNode* get_last(HashNode* node) 
{
    HashNode* result = node;
    while (get_next(result) != NULL) {
        result = get_next(result);
    }
    return result;
}

uint hash(HashTable* ht, const char* key)
{
    uint index = 5381;
    uint key_len = strlen(key); 
    uint table_size = ht->size;
    int c = *key++;
    //djb2 algorithm
    while (c) {
        index = ((index << 5) + index) + c;
        c = *key++;
    }
    
    return index % table_size;
}

void ht_insert(HashTable* ht, const char* key, void* pointer)
{
    HashNode** table = ht->table;
    int hash_index = hash(ht, key);
    HashNode* new_node = newNode(pointer);
    HashNode* found = ht_get_first(ht, key);
    if (found != NULL) { // If collision is detected
        HashNode* last_node = get_last(found);
        last_node->next_node = new_node;
        return;
    }
    table[hash_index] = new_node;
    return;
}

HashNode* ht_get_first(HashTable* ht, const char* key)
{
    HashNode** table = ht->table;
    int hash_index = hash(ht, key);
    return table[hash_index];
}

HashNode* ht_get_next(HashNode* node)
{
    if (node == NULL) {
        return NULL;
    }
    return node->next_node;
}

void ht_free(HashTable* ht)
{
    if (ht == NULL) return;
    HashNode** table = ht->table;
    int size = ht->size;
    for (int i = 0; i < size; i++) {
        HashNode* node = table[i];
        while (node != NULL) {
            HashNode* tmp = node;
            node = node->next_node;
            free(tmp);
        }
        table[i] = NULL;
    }
    free(ht->table);
    free(ht);
    return;
}

