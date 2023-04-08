#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "myqueue.h" // Подключаем собственный заголовочный файл

#define MAX_STR_LEN 250

void read_value(int* value)
{
    // Remember the return value of scanf
    int input_res = scanf("%d", value);
    while (input_res < 1) { // If a non-number was entered
        printf("Invalid value. Try again: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}; // Clear input buffer
        input_res = scanf("%d", value);
    }
    return;
}

void creation_menu()
{
    printf("\n\t|== Action Menu ==|\n");
    printf("\t1. Push element to queue\n");
    printf("\t2. Pop back from queue\n");
    printf("\t3. Sort with Hoare's Algorithm\n");
    printf("\t4. Print queue\n");
    printf("\t0. Finish\n");
}

int main() {

    bool try_again = true;

    while (try_again) {

        printf("How many queues would you like to work with?\n");
        int q_num;
        read_value(&q_num);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}; // Clear input buffer

        if (q_num <= 0) {
            printf("You've chosen not to work at all\n");
            return 0;
        }

        MyQueue* merged_queue = createQueue(); // Результирующая очередь
     
        for (int i = 0; i < q_num; i++) {
            MyQueue* temp_q = merged_queue;
            printf("Working with the queue <%d>...", i + 1);
            MyQueue* new_queue = createQueue();
            int choice;
            do {
                creation_menu();
                scanf("%d", &choice);
                switch(choice) {
                case 1:
                    printf("Enter value of the new element: ");
                    int value;
                    read_value(&value);
                    push_back(new_queue, value);
                    printf("Now queue looks like this:\n");
                    print_queue(new_queue);
                    break;

                case 2:
                    if (get_size(new_queue) == 0) {
                        printf("The queue is empty already.\n");
                        break;
                    }
                    pop_front(new_queue);
                    printf("Now queue looks like this:\n");
                    print_queue(new_queue);
                    break;

                case 3:
                    if (get_size(new_queue) == 0) {
                        printf("The queue is empty. Nothing to sort.\n");
                        break;
                    }
                    new_queue = quick_sort(new_queue);
                    printf("Now queue looks like this:\n");
                    print_queue(new_queue);
                    break;

                case 4:
                    if (get_size(new_queue) == 0) {
                        printf("The queue is empty.\n");
                        break;
                    }
                    printf("=--\n");
                    print_queue(new_queue);
                    printf("=--\n");
                    break;

                case 0:
                    printf("Moving on...\n");
                    break;

                default:
                    printf("Invalid choice. Please, choose a valid option.\n");
                }
            } while (choice != 0);
            // Функция join также очищает память двух входных очередей после слияния
            merged_queue = join(temp_q, new_queue); // Конкатенация двух очередей
        }
        
        if (get_size(merged_queue) != 0) {
            printf("Merging queues...\n");
            print_queue(merged_queue);
            printf("\n");
        }
        else {
            printf("Nothing to work with...\n");
        }

        // Освобождаем память
        free_queue(merged_queue);

        printf("Would you like to try again? [y/n]\n");
        char choice = ' ';
        while (!(choice == 'y' || choice == 'n')) {
            scanf(" %c", &choice);
            switch (choice) {
            case 'y':
                try_again = true;
                break;
            case 'n':
                try_again = false;
                break;
            default:
                printf("Incorrect input. Type 'y' or 'n': ");
                break;
            }
        }
    }

    return 0;
}