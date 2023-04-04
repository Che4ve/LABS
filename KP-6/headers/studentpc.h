#ifndef __STUDENTPC_H__
#define __STUDENTPC_H__

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../headers/dict.h"

#define SPECS_HT_SIZE 59 // Less will cause collisions
#define MAX_LEN 250
#define MAX_SPEC_SIZE 50

typedef struct _hash_table HashTable;

typedef struct _studentpc {
    // Name
    char* name;
    // CPU
    int cpu_num;
    char* cpus;
    // RAM
    int ram;
    // GPU
    char* gpu;
    int vram;
    // HDD
    int hdd_num;
    char* hdds;
    // Devices
    int device_num;
    // Operating System
    char* os;

    // Specs table
    HashTable* specs;

    // Coolness level
    int coolness;
} StudentPC;

StudentPC* newPC();

char* get_name(StudentPC* pc);

void read_spec_from(const char* type, void* spec_p, char* input_p);

void csv_read(StudentPC* pc, char* input_s);

void* specstostr(StudentPC* pc, char* str);

#endif