#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "poemsort.h"

#define MAX_SIZE 100

void startMenu(void)
{
    printf("    1. Print initial poem.\n");
    printf("    2. Print sorted poem.\n");
    printf("    3. Find line by key.\n");
    printf("    0. Quit.\n");
}

int main(int argc, char** argv)
{
    if (argc != 2 || argv[1] == NULL) {
        printf("Usage: main.out <data_file.txt>\n");
        exit(1);
    }
    char filename[MAX_LEN];
    strncpy(filename, argv[1], MAX_LEN - 1);
    filename[MAX_LEN - 1] = '\0';
    FILE* fp;
    fp = fopen(filename, "r");

    Lines initialPoem = calloc(MAX_SIZE, sizeof(DataLine*));
    Lines sortedPoem = calloc(MAX_SIZE, sizeof(DataLine*));

    int poemLen = readPoem(fp, initialPoem);

    for (int i = 0; i < poemLen; i++) {
        sortedPoem[i] = initialPoem[i];
    }

    quickSort(sortedPoem, poemLen);
    
    
    int choice;
    do {
        startMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                printf("===\n");
                printPoem(initialPoem, poemLen);
                sortType type = getSortType(initialPoem, poemLen);
                switch (type) {
                    case ASCENDING: {
                        printf("<Ascending order>\n");
                        break;
                    }
                    case DESCENDING: {
                        printf("<Descending order>\n");
                        break;
                    }
                    case UNSORTED: {
                        printf("<Unsorted>\n");
                        break;
                    }
                }
                printf("===\n");
                break;
            }
            case 2: {
                printf("===\n");
                printPoem(sortedPoem, poemLen);
                printf("===\n");
                break;
            }
            case 3: {
                double key;
                printf("Enter key: ");
                scanf("%lf", &key);
                int found = findInPoem(sortedPoem, key, 0, poemLen - 1);
                if (found != -1) {
                    printf("Line: %s\n", sortedPoem[found]->text);\
                }
                else {
                    printf("No such key in the table.\n");
                }
                break;
            }
            case 0: {
                burnPoem(initialPoem, poemLen);
                break;
            }
        }
    } while (choice != 0);

    fclose(fp);
    return 0;
}
