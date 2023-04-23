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

int convert_file(char* filename)
{
    char* extension = strrchr(filename, '.');
    if (extension != NULL && strcmp(extension, ".txt") != 0) {
        fprintf(stderr, "The file '%s' does not have the expected extension.\n", filename);
        return -1;
    }
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
    char* file_bin = _strdup(basename);
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
        if (csv_read(pc, buffer) != 0) {
            fprintf(stderr, "Converting Error: wrong or missing data.\n");
            return -1;
        }
        bin_write(pc, fp_out);
        pc_free(pc);
    }
    // Close both files
    fclose(fp_in);
    fclose(fp_out);
    printf("Done. Created \"%s\"\n", file_bin);
    return 0;
}

int main(int argc, char **argv) 
{
    int num;
    if (argc < 2) {
        printf("Usage: conv.out <text_file> ..\n");
        exit(1);
    }
    for (int i = 1; i < argc; i++) {
        if (convert_file(argv[i]) == -1) {
            return -1;
        }
    }
    return 0;
}