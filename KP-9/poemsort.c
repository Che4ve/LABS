#include "poemsort.h"

DataLine* initDataLine(void)
{
    DataLine* newLine = (DataLine*)malloc(sizeof(DataLine));
    newLine->text = calloc(MAX_LEN, sizeof(char));
    return newLine;
}

void swapLines(DataLine** a, DataLine** b) 
{
    DataLine* temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Lines arr, int low, int high) 
{
    double pivot = arr[ (low + high) / 2]->key;
    int i = low;
    int j = high;
    while (i < j) {
        while (arr[i]->key < pivot) {
            i++;
        }
        while (arr[j]->key > pivot) {
            j--;
        }
        if (i >= j) {
            break;
        }
        swapLines(&arr[i], &arr[j]);
    }
    return j;
}

void quickSort(Lines arr, size_t size)
{
    int stack[MAX_STACK_SIZE];
    int top = -1; // stack upper element index
    stack[++top] = 0; // lower border
    stack[++top] = (int)size - 1; // upper border
    while (top >= 0) { // while stack has elements
        // getting two last borders
        int rightBorder = stack[top--];
        int leftBorder = stack[top--];
        if ( leftBorder >= rightBorder ) {
            continue;
        }
        // getting split
        int split = partition(arr, leftBorder, rightBorder);
        // putting borders of subarrays to stack
        stack[++top] = leftBorder;
        stack[++top] = split - 1;
        stack[++top] = split + 1;
        stack[++top] = rightBorder;
    }
}

sortType getSortType(Lines arr, size_t size)
{
    int isAscending = 1;
    int isDescending = 1;
    for (int i = 1; i < size; i++) {
        if (arr[i]->key < arr[i - 1]->key) {
            isAscending = 0;
        } else if (arr[i]->key > arr[i - 1]->key) {
            isDescending = 0;
        }
    }
    if (isAscending) {
        return ASCENDING;
    }
    else if (isDescending) {
        return DESCENDING;
    }
    else {
        return UNSORTED;
    }
}

int findInPoem(Lines arr, double key, size_t leftBound, size_t rightBound)
{
    const double epsilon = 1E-3;
    int index = (int)(leftBound + rightBound) / 2;
    while (leftBound < rightBound) {
        double currentKey = arr[index]->key;
        
        if (fabs(currentKey - key) < epsilon) {
            return index;
        }

        if (currentKey < key) {
            leftBound = index + 1;
        }
        else {
            rightBound = index - 1;
        }
        index = (int)(leftBound + rightBound) / 2;
    }
    if (fabs(arr[index]->key - key) < epsilon) {
        return index;
    }
    return -1;
}

int readPoem(FILE *fp, Lines arr)
{
    char buffer[MAX_LEN];
    buffer[MAX_LEN - 1] = '\0';
    int poemLen = 0;
    while (fgets(buffer, MAX_LEN, fp) != NULL) {
        char* line = strdup(buffer);
        DataLine* data = initDataLine();    
        data->key = strtod(line, &line);
        strncpy(data->text, line + 1, MAX_LEN);
        if (data->text[0] == '\0') {
            break;
        }
        arr[poemLen++] = data;
    }
    return poemLen;
}

void printPoem(Lines arr, size_t size)
{
    for (int i = 0; i < size; i++) {
        printf("%4.1lf %s", arr[i]->key, arr[i]->text);
    }
}

void burnPoem(Lines arr, size_t size)
{
    for (int i = 0; i < size; i++) {
        free(arr[i]->text);
        free(arr[i]);
    }
    free(arr);
}
