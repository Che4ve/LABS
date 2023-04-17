#include "../headers/dict.h"

//typedef unsigned int uint;

HashTable* createTable(int table_size)
{
    HashTable* new_ht = malloc(sizeof(HashTable));
    new_ht->table = calloc(table_size, sizeof(HashNode));
    new_ht->size = table_size;
    return new_ht;
}

HashNode* newNode(void* value_p)
{
    HashNode* new_node = malloc(sizeof(HashNode));
    new_node->value = value_p;
    new_node->next_node = NULL;
    return new_node;
}

void ht_free(HashTable* ht)
{
    HashNode** table = ht->table;
    int size = ht->size;
    for (int i = 0; i < size; i++) {
        free(table[i]);
    }
    free(table);
    free(ht);
    return;
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
    int c;
    //djb2 algorithm
    while (c = *key++) {
        index = ((index << 5) + index) + c;
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

void ht_print(HashTable* ht)
{
    int size = ht->size;
    HashNode** table = ht->table;
    for (int i = 0; i < size; i++) {
        HashNode* current_node = table[i];
        if (current_node == NULL) {
            continue;
        }
        printf("||============||==================||=====||\n");
        do {
            StudentPC* pc = get_value(current_node);
            char* name = get_name(pc);
            char spec_list[MAX_LEN];
            specstostr(pc, spec_list);
            printf("|| %10s || %30s ||\n", name, spec_list);
            current_node = get_next(current_node);
        } while (current_node != NULL);
    }
    printf("||============||==================||=====||\n");
    return;
}

void ht_print_specs(StudentPC* pc)
{
    HashTable* ht = pc->specs;

    char* name = ht_get_first(ht, "name")->value;
    int* cpu_n = ht_get_first(ht, "cpu_n")->value;
    char* cpus = ht_get_first(ht, "cpus")->value;
    int* ram = ht_get_first(ht, "ram")->value;
    char* gpu = ht_get_first(ht, "gpu")->value;
    int* vram = ht_get_first(ht, "vram")->value;
    int* hdd_n = ht_get_first(ht, "hdd_n")->value;
    char* hdds = ht_get_first(ht, "hdds")->value;
    int* device_n = ht_get_first(ht, "device_n")->value;
    char* os = ht_get_first(ht, "os")->value;

    printf("|==========================================|\n");
    printf("|\t%s PC\t                   |\n", name);
    printf("|=========|================================|\n");
    printf("| CPU num | %15d\t\t   |\n", *cpu_n);
    printf("|=========|================================|\n");
    printf("|  CPUs   | %27s\t   |\n", cpus);
    printf("|=========|================================|\n");
    printf("|   RAM   | %15d\t\t   |\n", *ram);
    printf("|=========|================================|\n");
    printf("|   GPU   |     %15s\t\t   |\n", gpu);
    printf("|=========|================================|\n");
    printf("|  VRAM   | %15d\t\t   |\n", *vram);
    printf("|=========|================================|\n");
    printf("| HDD num | %15d\t\t   |\n", *hdd_n);
    printf("|=========|================================|\n");
    printf("|  HDDs   |   %15s\t\t   |\n", hdds);
    printf("|=========|================================|\n");
    printf("| Devices | %15d\t\t   |\n", *device_n);
    printf("|=========|================================|\n");
    printf("|   OS    |     %15s\t\t   |\n", os);
    printf("|=========|================================|\n");
    return;
}
