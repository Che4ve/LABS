#ifndef __STUDENTPC_H__
#define __STUDENTPC_H__

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../headers/globals.h"

#define SPECS_COUNT 9
#define SPECS_HT_SIZE 59 // Less will cause collisions

typedef struct _hash_table HashTable;

typedef struct _key_spec {
    const char* key;
    void* spec_p;
} KeySpec;

typedef struct _studentpc {
    char* name;
    int cpu_num;
    char* cpus;
    int ram;
    char* gpu;
    int vram;
    int hdd_num;
    char* hdds;
    int device_num;
    // Operating System
    char* os;
    // Specs table
    HashTable* specs;
} StudentPC;

StudentPC* newPC();

char* get_name(StudentPC* pc);

void* get_spec(StudentPC* pc, const char* key);

int read_spec_from(const char* type, void* spec_p, char* input_p);

int csv_read(StudentPC* pc, char* input_s);

void specstostr(StudentPC* pc, char* str, size_t len);

int bin_read(StudentPC *pc, FILE* fp);

int bin_write(StudentPC *pc, FILE *fp);

void pc_print_specs(StudentPC* pc);

int pc_print_table(HashTable* ht);

void pc_free(StudentPC *pc);

#endif