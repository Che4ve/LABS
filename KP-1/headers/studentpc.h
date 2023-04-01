#ifndef __STUDENTPC_H__
#define __STUDENTPC_H__

#include <string.h>
#include <stdlib.h>

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
    int gmem;
    // HDD
    int hdd_num;
    char* hdds;
    // Devices
    int device_num;
    // Operating System
    char* os;
    // Coolness level
    int coolness;
} StudentPC;

StudentPC* newPC();

#endif