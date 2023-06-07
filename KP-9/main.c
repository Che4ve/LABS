#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "poemsort.h"
#define MAX_SIZE 100
 // Function to display the start menu options
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
    Lines sortedPoem;
    int poemLen = readPoem(fp, initialPoem);
    sortType type = getSortType(initialPoem, poemLen);
    if (type != UNSORTED) {
        sortedPoem = initialPoem;
    }
    else {
        sortedPoem = calloc(MAX_SIZE, sizeof(DataLine*));
        for (int i = 0; i < poemLen; i++) {
            sortedPoem[i] = initialPoem[i];
        }
        quickSort(sortedPoem, poemLen);
    }
    int choice;
    // Options enumeration
    enum {
        PRINT_INIT   = 1,
        PRINT_SORTED = 2,
        FIND_LINE    = 3,
        QUIT         = 0
    };
    do {
        startMenu();
        scanf("%d", &choice);
        switch (choice) {
            case PRINT_INIT: {
                printf("===\n");
                printPoem(initialPoem, poemLen);
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
            case PRINT_SORTED: {
                printf("===\n");
                printPoem(sortedPoem, poemLen);
                printf("===\n");
                break;
            }
            case FIND_LINE: {
                double key;
                printf("Enter key: ");
                scanf("%lf", &key);
                int found = findInPoem(sortedPoem, key, 0, poemLen - 1, type);
                if (found != -1) {
                    printf("Line: %s\n", sortedPoem[found]->text);
                }
                else {
                    printf("No such key in the table.\n");
                }
                break;
            }
            case QUIT: {
                break;
            }
            default: {
                printf("Incorrect input. Try again.\n");
                break;
            }
        }
    } while (choice != QUIT);
    burnPoem(initialPoem, poemLen);
    if (type == UNSORTED) {
        free(sortedPoem);
    }
    fclose(fp);
    return 0;
}