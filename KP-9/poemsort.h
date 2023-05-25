#ifndef __POEMSORT_H__
#define __POEMSORT_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LEN 250
#define MAX_STACK_SIZE 2048

typedef struct {
    double key;
    char* text;
} DataLine;

DataLine* initDataLine();

typedef DataLine** Lines;

void swapLines(DataLine** a, DataLine** b);

int partition(Lines arr, int low, int high);

void quickSort(Lines arr, size_t size);

typedef enum {
    UNSORTED,
    ASCENDING,
    DESCENDING,
} sortType;

sortType getSortType(Lines arr, size_t size);

int findInPoem(Lines arr, double key, size_t leftBound, size_t rightBound);

int readPoem(FILE *fp, Lines arr);

void printPoem(Lines arr, size_t size);

void burnPoem(Lines arr, size_t size);

#endif 
