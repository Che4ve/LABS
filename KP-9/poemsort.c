#include "poemsort.h"
 // Initialize a new DataLine object with memory allocation
DataLine* initDataLine(void)
{
    DataLine* newLine = (DataLine*)malloc(sizeof(DataLine));
    newLine->text = calloc(MAX_LEN, sizeof(char));
    return newLine;
}
 // Swap two DataLine objects
void swapLines(DataLine** a, DataLine** b) 
{
    DataLine* temp = *a;
    *a = *b;
    *b = temp;
}
 // Partition function for quicksort algorithm
int partition(Lines arr, int low, int high) 
{
    double pivot = arr[(low + high) / 2]->key;
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
 // Quick sort function for sorting DataLine objects
void quickSort(Lines arr, size_t size)
{
    int stack[MAX_STACK_SIZE];
    int top = -1; // stack upper element index
    stack[++top] = 0; // lower border
    stack[++top] = (int)size - 1; // upper border
     // While stack has elements
    while (top >= 0) { 
        // Getting two last borders
        int rightBorder = stack[top--];
        int leftBorder = stack[top--];
         if (leftBorder >= rightBorder) {
            continue;
        }
         // Getting split
        int split = partition(arr, leftBorder, rightBorder);
         // Putting borders of subarrays to stack
        stack[++top] = leftBorder;
        stack[++top] = split - 1;
        stack[++top] = split + 1;
        stack[++top] = rightBorder;
    }
}
 // Determine the sort type of the given array
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
    } else if (isDescending) {
        return DESCENDING;
    } else {
        return UNSORTED;
    }
}
 // Find the index of a key in the given array within the specified bounds
int findInPoem(Lines arr, double key, size_t leftBound, size_t rightBound, sortType type)
{
    const double epsilon = 1E-3;
    int index = (int)(leftBound + rightBound) / 2;
     while (leftBound < rightBound) {
        double currentKey = arr[index]->key;
         if (fabs(currentKey - key) < epsilon) {
            return index;
        }
        // Comparasion depends on a sort type
        if ((type == ASCENDING && currentKey < key) || (type == DESCENDING && currentKey > key)) {
            leftBound = index + 1;
        } else {
            rightBound = index - 1;
        }
         index = (int)(leftBound + rightBound) / 2;
    }
     if (fabs(arr[index]->key - key) < epsilon) {
        return index;
    }
     return -1;
}
 // Read the poem from the file and store it in the given array
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
 // Print the poem to the console
void printPoem(Lines arr, size_t size)
{
    for (int i = 0; i < size; i++) {
        printf("%4.1lf %s", arr[i]->key, arr[i]->text);
    }
}
 // Free memory allocated for the poem
void burnPoem(Lines arr, size_t size)
{
    for (int i = 0; i < size; i++) {
        free(arr[i]->text);
        free(arr[i]);
    }
    free(arr);
}