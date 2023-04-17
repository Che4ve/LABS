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
    // Name
    char name[SPEC_SIZE];
    // CPU
    int cpu_num;
    char cpus[SPEC_SIZE];
    // RAM
    int ram;
    // GPU
    char gpu[SPEC_SIZE];
    int vram;
    // HDD
    int hdd_num;
    char hdds[SPEC_SIZE];
    // Devices
    int device_num;
    // Operating System
    char os[SPEC_SIZE];
    // Specs table
    HashTable* specs;
} StudentPC;

StudentPC* newPC();

void pc_free(StudentPC *pc);

char* get_name(StudentPC* pc);

void* get_spec(StudentPC* pc, const char* key);

void read_spec_from(const char* type, void* spec_p, char* input_p);

void csv_read(StudentPC* pc, char* input_s);

int bin_read(StudentPC *pc, FILE* fp);

void* specstostr(StudentPC* pc, char* str);

#endif