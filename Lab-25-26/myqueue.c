#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "myqueue.h"

typedef struct _queue_node { // Структура узла очереди
    int value;
    struct _queue_node* next_node;
} QueueNode;

typedef struct _my_queue { // Структура очереди (размер, нач. и конеч. узлы)
    int size;
    QueueNode* front; // Первый элемент
    QueueNode* back; // Последний элемент
} MyQueue;

MyQueue* createQueue() // Создание пустой очереди
{
    MyQueue* new_queue = (MyQueue*)malloc(sizeof(MyQueue)); // Резервируем память
    new_queue->size = 0;
    new_queue->front = NULL;
    new_queue->back = NULL;
    return new_queue;
}

QueueNode* newNode(int value) // Конструктор узла
{
    QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode)); // Резервируем память
    new_node->value = value;
    new_node->next_node = NULL;
    return new_node;
}

int get_size(MyQueue* queue)
{
    if (queue == NULL) {
        return 0;
    }
    return queue->size;
}

void free_queue(MyQueue* queue) // Освобождение памяти, занимаемой очередью
{
    QueueNode* current_node = queue->front;
    if (current_node == NULL) {
        free(queue);
        return;
    }
    QueueNode* temp_ptr; // Временная ссылка на узел
    for (int i = 0; i < queue->size; i++) {
        temp_ptr = current_node;
        current_node = current_node->next_node;
        free(temp_ptr); // Удаление по временной ссылке
    }
    free(queue);
    return;
}

void push_back(MyQueue* queue, QueueNode* node) // Добавление элемента в конец
{
    if (node == NULL || queue == NULL) { // Если узел не имеет смысла
        return;
    }
    if (queue->back == NULL) { // Если очередь ещё пуста
        queue->back = queue->front = node;
        queue->size++;
        return;
    }
    queue->back->next_node = node;
    queue->back = node;
    node->next_node = NULL;
    queue->size++;
    return;
}

int pop_front(MyQueue* queue) // Извлекаем узел из начала очереди
{
    if (queue->front == NULL) { // Если нет элементов в очереди
        return INT_MIN;
    }
    QueueNode* front_node = queue->front;
    int value = front_node->value; // Значение узла (лок. переменная)

    queue->front = front_node->next_node;
    free(front_node); // Очищаем память по ссылке
    front_node = NULL;
    queue->size--;

    return value;
}

MyQueue* join(MyQueue* q1, MyQueue* q2) // Конкатенация двух очередей
{
    MyQueue* result = createQueue(); // Создаем результирующую очередь
    while (get_size(q1) > 0) {
        int current_value = pop_front(q1);
        push_back(result, newNode(current_value));
    }
    while (get_size(q2) > 0) {
        int current_value = pop_front(q2);
        push_back(result, newNode(current_value));
    }
    free_queue(q1);
    free_queue(q2);
    return result;
}

MyQueue* copy_queue(MyQueue* queue)
{   
    MyQueue* result = createQueue();
    int initial_size = queue->size;
    for ( int i = 0; i < initial_size; i++ ) {
        int copied_value = pop_front(queue);
        push_back(queue, newNode(copied_value));
        push_back(result, newNode(copied_value));
    }
    return result;
}

void print_queue(MyQueue* queue) // Вывод очереди
{
    printf("====== ");
    QueueNode* current_node = queue->front;
    for (int i = 0; i < get_size(queue); i++) {
        if (i == get_size(queue) - 1) {
            printf("{%d} ====== Size: %d\n", current_node->value, queue->size);
        } else {
            printf("{%d} ", current_node->value);
        }
        current_node = current_node->next_node;
    }
    return;
}

MyQueue* quick_sort(MyQueue* queue) // Быстрая сортировка Хоара
{
    if (queue->size <= 1) { // Условие выхода из рекурсии

        return queue;
    }

    MyQueue* left_q = createQueue(); // Левая очередь
    MyQueue* right_q = createQueue(); // Правая очередь

    // Опорный узел - первый узел входной очереди
    int pivot = pop_front(queue); // Значение опорного узла
    while ( get_size(queue) > 0) {
        int current_value = pop_front(queue);
        if (current_value < pivot) {
            push_back(left_q, newNode(current_value));
        } else {
            push_back(right_q, newNode(current_value));
        }
    }
    // Добавляем опорный узел в левую очередь
    push_back(left_q, newNode(pivot));

    // Освобождаем обработанную очередь
    free_queue(queue);

    // Рекурсия
    queue = join(quick_sort(left_q), quick_sort(right_q));

    return queue;
}
