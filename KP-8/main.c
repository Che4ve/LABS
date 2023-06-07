#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "linlist.h"

#define MAX_LEN 250

Complex parseComplexNumber(char* str) 
{
    Complex number;
    char oper = ' ';
    char* c = str;
    double real = 0.0;
    double imaginary = 0.0;
    int part = 0;
    while (*c != '\0') {
        if (*c == '+' || *c == '-') {
            oper = *c;
            c++;
            continue;
        }
        char* prev_c = c;
        double value;
        value = strtod(c, &c);
        if (c != prev_c) {
            if (oper == '-') {
                value = - value;
            }
            if (part == 0) {
                real = value;
                part = 1;
            }
            else if (part == 1) {
                imaginary = value;
                break;
            }
            oper = ' ';
        }
        c++;
    }
    number = (Complex){real, imaginary};
    return number;
}

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
                char str[MAX_LEN + 1];
                str[MAX_LEN] = '\0';
                Complex value;
                printf("========================\n");
                printf("Enter the index (array size is %d): ", getSize(&list));
                scanf("%d", &index);
                getchar();
                printf("Enter the complex number (e.g., 1 + 3i): ");
                fgets(str, MAX_LEN, stdin);
                str[strcspn(str, "\n")] = '\0'; 
                value = parseComplexNumber(str);
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