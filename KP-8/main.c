#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linlist.h"

void printMenu() { // функция меню
    printf("1. Add an element.\n");
    printf("2. Remove an element.\n");
    printf("3. Get the size of the list.\n");
    printf("4. Remove every k-th element.\n");
    printf("5. Print the list on the screen.\n");
    printf("0. Exit.\n");
}

int main(int argc, char **argv) {
    LinearList list;
    initList(&list);

    int choice;
    do {
        printMenu();
        printf("========================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int index;
                Complex value;
                printf("========================\n");
                printf("Enter the index (array size is %d): ", getSize(&list));
                scanf("%d", &index);
                printf("Enter the real part: ");
                scanf("%lf", &value.real);
                printf("Enter the imaginary part: ");
                scanf("%lf", &value.imaginary);
                insertElement(&list, index, value);
                break;
            }
            case 2: {
                int index;
                printf("========================\n");
                printf("Enter the index (array size is %d): ", getSize(&list));
                scanf("%d", &index);
                removeElement(&list, index);
                break;
            }
            case 3: {
                int size = getSize(&list);
                printf("========================\n");
                printf("Size of the list: %d\n", size);
                break;
            }
            case 4: {
                int k;
                printf("========================\n");
                printf("Enter k: ");
                scanf("%d", &k);
                removeEveryKthElement(&list, k);
                break;
            }
            case 5: {
                printf("========================\n");
                printList(&list);
                break;
            }
            case 0: {
                printf("========================\n");
                printf("Exiting the program.\n");
                break;
            }
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

        printf("========================\n");

    } while (choice != 0);

    destroyList(&list);
    return 0;
}