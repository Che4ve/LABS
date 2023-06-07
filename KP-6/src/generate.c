#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "../headers/globals.h"

#define max(a, b) ((((int) a) > ((int) b)) ? ((int) a) : ((int) b))

// RANDOMIZATION
int rand_volume(int ceil)
{
    int rand_num = rand() % ceil;
    rand_num =  max(rand_num, 1);
    int result = (int) pow(2, floor(log2(rand_num)));
    return max(result, 2);
}

void rand_cpus(char* destination, int* cpu_n)
{
    int cpu_num = rand() % MAX_CPUS;
    cpu_num = max(cpu_num, 1);
    char result[SPEC_SIZE] = { 0 };
    for (int i = 0; i < cpu_num; i++) {
        char* rand_cpu = strdup(allowed_cpus[rand() % NUM_ALWD_CPUS]);
        strcat(result, rand_cpu);
        if (i != cpu_num - 1) {
            strcat(result, "|");
        }
    }
    *cpu_n = cpu_num;
    strcpy(destination, result);
    return;
}

void rand_gpu(char* destination)
{
    char result[SPEC_SIZE];
    strcpy(result, allowed_gpus[rand() % NUM_ALWD_GPUS]);
    strcpy(destination, result);
    return;
}

void rand_hdds(char* destination, int* hdd_n)
{
    int hdd_num = rand() % MAX_HDDS;
    hdd_num = max(hdd_num, 1);
    char result[SPEC_SIZE] = { 0 };
    for (int i = 0; i < hdd_num; i++) {
        int rand_hdd = rand() % MAX_LTM;
        rand_hdd = max(rand_hdd, 1);
        char str_hdd[SPEC_SIZE];
        sprintf(str_hdd, "%dTB", rand_hdd);
        strcat(result, str_hdd);
        if (i != hdd_num - 1) {
            strcat(result, "|");
        }
    }
    *hdd_n = hdd_num;
    strcpy(destination, result);
    return;
}

void rand_os(char* destination)
{
    char result[SPEC_SIZE];
    strcpy(result, allowed_os[rand() % NUM_ALWD_OS]);
    strcpy(destination, result);
    return;
}

// FILE GENERATOR
int generate_file(char* filename)
{
    char* extension = strrchr(filename, '.');
    if (extension != NULL && strcmp(extension, ".txt") != 0) {
        fprintf(stderr, "The file '%s' does not have the expected extension.\n", filename);
        return -1;
    }
    FILE* fp;
    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error");
        exit(ENOENT);
    }
    int iter_num = rand() % MAX_STUDENTS;
    iter_num = max(iter_num, 1);
    for (int i = 0; i < iter_num; i++) {
        char* name = strdup(allowed_names[rand() % NUM_ALWD_NAMES]);
        int cpu_n;
        char cpus[SPEC_SIZE];
        rand_cpus(cpus, &cpu_n);
        int ram = rand_volume(MAX_RAM);
        char gpu[SPEC_SIZE];
        rand_gpu(gpu);
        int vram = rand_volume(MAX_VRAM);
        int hdd_n;
        char hdds[SPEC_SIZE];
        rand_hdds(hdds, &hdd_n);
        int device_n = (rand() % MAX_DEVICES);
        device_n = max(device_n, 1);
        char os[SPEC_SIZE];
        rand_os(os);

        fprintf(fp, "%s,%d,%s,%dGB,%s,%dGB,%d,%s,%d,%s\n", \
            name, \
            cpu_n, \
            cpus, \
            ram, \
            gpu, \
            vram, \
            hdd_n, \
            hdds, \
            device_n, \
            os);
    }
    fclose(fp);
    printf("Done. Created \"%s\"\n", filename);
    return 0;
}

int main(int argc, char** argv)
{
    srand(time(NULL));  // set the seed for rand()
    if (argc < 2) {
        printf("Usage: gen.out <new_file_name> ..\n");
        exit(1);
    }
    for (int i = 1; i < argc; i++) {
        if (generate_file(argv[i]) == -1) {
            return -1;
        };
    }
    return 0;
}