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

// Get a queue by a string with nodes values
MyQueue* scan_queue(MyQueue* queue, char* nodes)
{
    char* cursor = nodes; // Pointer to the beginning of the string (cursor)
    while (cursor < nodes + strlen(nodes) - 1) { // Until the cursor reaches the end of the string
        char* endptr; // Pointer to the place after the number
        long value = strtol(cursor, &endptr, 10); // Get the number from the string
        // Skip empty spaces
        while (*endptr == ' ') {
            endptr++;
        }
        // If the number couldn't be inputted or the child node number is incorrect
        if (endptr == cursor) {
            printf("incorrect input. Please, try again from the place you've made a mistake: ");
            return NULL;
        }
        // Update cursor for reading the next number
        push_back(queue, newNode(value));
        cursor = endptr;
    }
    return queue;
}

int main() {

    bool try_again = true;

    while (try_again) {

        printf("How many queue structures would you like to merge?\n");
        int q_num = -1;
        read_value(&q_num);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}; // Clear input buffer

        if (q_num <= 0) {
            printf("You've chosen not to merge any queues\n");
            return 0;
        }

        MyQueue* merged_queue = createQueue(); // Результирующая очередь
        MyQueue* new_queue = NULL; // Следующая очередь по списку

        for (int i = 0; i < q_num; i++) {
            new_queue = createQueue();
            MyQueue* temp_q = merged_queue;
            printf("Please, enter the <%d> queue (for example, '0 1 2 3'): ", i + 1);
            MyQueue* result = NULL;
            do {
                char nodes[MAX_STR_LEN];
                fgets(nodes, MAX_STR_LEN, stdin); // Read the string from stdin
                result = scan_queue(new_queue, nodes);
            } while (result == NULL);
            
            if (get_size(new_queue) == 0) {
                printf("That's an empty queue\n");
            }
            else {
                printf("You've constructed a queue:\n");
                print_queue(new_queue);
            }
            printf("\n");

            // Функция join также очищает память двух входных очередей после слияния
            merged_queue = join(temp_q, new_queue); // Конкатенация двух очередей
        }

        if (get_size(merged_queue) != 0) {
            printf("Merging queues...\n");
            print_queue(merged_queue);
            printf("\n");

            printf("Sorting queue using quick sort...\n");
            merged_queue = quick_sort(merged_queue); // Быстрая сортировка Хоара
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