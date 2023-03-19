#include <stdlib.h>
#include <stdio.h>
#include "myqueue.h" // Подключаем собственный заголовочный файл

int main() {
    MyQueue* queue = createQueue();

    printf("queue #1...\n");
    push_back(queue, newNode(11));
    push_back(queue, newNode(10));
    push_back(queue, newNode(20));
    push_back(queue, newNode(4));
    push_back(queue, newNode(12));
    push_back(queue, newNode(7));
    push_back(queue, newNode(5));
    print_queue(queue);

    MyQueue* q2 = createQueue(); 
    push_back(q2, newNode(2));
    push_back(q2, newNode(1));
    push_back(q2, newNode(0));

    printf("queue #2...\n");
    print_queue(q2);

    queue = join(queue, q2);
    
    queue = quick_sort(queue);

    print_queue(queue);

    return 0;
}