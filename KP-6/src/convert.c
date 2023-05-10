#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/globals.h"

// function prototypes
StudentPC* newPC();
int csv_read(StudentPC* pc, char* buffer);

typedef struct _record {
    char Surname[SPEC_SIZE];
    int ProcessorsNumber;
    char CPUs[SPEC_SIZE];
    int Memory;
    char NvidiaGPU[SPEC_SIZE];
    int GraphicalMemory;
    int HDDsNumber;
    char HDDs[SPEC_SIZE];
    int DevicesNumber;
    char OS[SPEC_SIZE];
} Record;

void convert_file(char* filename)
{
    FILE *fp_in, *fp_out;
    
    // Open the text file for reading
    fp_in = fopen(filename, "r");
    if (fp_in == NULL) {
        perror("Error");
        exit(ENOENT);
    }
    char basename[MAX_LEN];
    char *dot = strrchr(filename, '.');
    if (dot) {
        strncpy(basename, filename, dot - filename);
        basename[dot - filename] = '\0';
    } else {
        strcpy(basename, filename);
    }
    char* file_bin = strdup(basename);
    strcat(file_bin, ".bin");

    // Open the binary file for writing
    fp_out = fopen(file_bin, "wb");
    if (fp_out == NULL) {
        printf("Error: Cannot create bin file for %s\n", filename);
        exit(1);
    }
    char buffer[MAX_LEN];
    // Read data from the text file and write to the binary file
    while (fgets(buffer, MAX_LEN, fp_in) != NULL) {
        StudentPC* pc = newPC();
        csv_read(pc, buffer);
        fwrite(pc->name,          sizeof(char), SPEC_SIZE, fp_out);
        fwrite(&(pc->cpu_num),    sizeof(int), 1, fp_out);
        fwrite(pc->cpus,          sizeof(char), SPEC_SIZE, fp_out);
        fwrite(&(pc->ram),        sizeof(int), 1, fp_out);
        fwrite(pc->gpu,           sizeof(char), SPEC_SIZE, fp_out);
        fwrite(&(pc->vram),       sizeof(int), 1, fp_out);
        fwrite(&(pc->hdd_num),    sizeof(int), 1, fp_out);
        fwrite(pc->hdds,          sizeof(char), SPEC_SIZE, fp_out);
        fwrite(&(pc->device_num), sizeof(int), 1, fp_out);
        fwrite(pc->os,            sizeof(char), SPEC_SIZE, fp_out);
        pc_free(pc);
    }
    // Close both files
    fclose(fp_in);
    fclose(fp_out);
    printf("Done. Created \"%s\"\n", file_bin);
}

int main(int argc, char **argv) 
{
    int num;
    if (argc < 2) {
        printf("Usage: conv.out <text_file> ..\n");
        exit(1);
    }
    for (int i = 1; i < argc; i++) {
        convert_file(argv[i]);
    }
    return 0;
}