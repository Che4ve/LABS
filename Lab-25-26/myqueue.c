#include <stdio.h>
#include <stdlib.h>
#include "myqueue.h"

typedef struct _queue_node {
    int value;
    struct _queue_node* next_node;
} QueueNode;

typedef struct _my_queue {
    int size;
    QueueNode* front; // Первый элемент
    QueueNode* back; // Последний элемент
} MyQueue;

MyQueue* createQueue() 
{
    MyQueue* new_queue = (MyQueue*)malloc(sizeof(MyQueue));
    new_queue->size = 0;
    new_queue->front = NULL;
    new_queue->back = NULL;
    return new_queue;
}

QueueNode* newNode(int value)
{
    QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
    new_node->value = value;
    new_node->next_node = NULL;
    return new_node;
}

void push_back(MyQueue* queue, QueueNode* node)
{
    if (queue->back == NULL) {
        queue->back = queue->front = node;
        queue->size++;
        return;
    }
    queue->back->next_node = node;
    queue->back = node;
    queue->size++;
    return;
}

void pop_front(MyQueue* queue)
{
    if (queue->front == NULL) { // Если нет элементов в очереди
        return;
    }
    QueueNode* front_node = queue->front;
    if (front_node->next_node == NULL) { // Если нет следующего элемента
        front_node = NULL;
        queue->size--;
        return;
    }
    queue->front = front_node->next_node;
    free(front_node);
    queue->size--;
    return;
}

MyQueue* join(MyQueue* q1, MyQueue* q2)
{
    if (q1->front == NULL || q2->front == NULL) {
        return;
    } 
    QueueNode* last_q1 = q1->back;
    QueueNode* first_q2 = q2->front;
    last_q1->next_node = first_q2;
    q1->size += q2->size;
    return q1;
}

void print_queue(MyQueue* queue)
{
    QueueNode* current_node = queue->front;

    for (int i = 0; i < queue->size; i++) {
        if (current_node->next_node == NULL) {
            printf("(%d), size: %d\n", current_node->value, queue->size);
        } else {
            printf("(%d) <- ", current_node->value);
        }
        current_node = current_node->next_node;
    }
    return;
}

MyQueue* quick_sort(MyQueue* queue)
{
    if (queue->size <= 1){
        return queue;
    }
    int q_size = queue->size;
    int pivot_id = q_size / 2;
    QueueNode* pivot = queue->front;
    for (int i = 0; i < pivot_id; i++) {
        pivot = pivot->next_node;
    }

    QueueNode* current_node = queue->front;
    MyQueue* left_q = createQueue();
    MyQueue* right_q = createQueue();;

    int p_value = pivot->value;

    for (int i = 0; i < q_size; i++) {
        int c_value = current_node->value;
        printf("(%d)\n", i);
        if (c_value < p_value){
            push_back(left_q, newNode(c_value));
        } else {
            push_back(right_q, newNode(c_value));
        }
        if (current_node->next_node != NULL) {
            current_node = current_node->next_node;
        }
    }

    left_q = quick_sort(left_q);
    right_q = quick_sort(right_q);

    join(left_q, right_q);
    
    MyQueue res = *left_q;
    free(left_q);
    free(right_q);

    return &res;
}
