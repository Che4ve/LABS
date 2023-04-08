// ЗАГОЛОВОЧНЫЙ ФАЙЛ КАСТОМНОЙ ОЧЕРЕДИ
#ifndef __MYQUEUE_H__
#define __MYQUEUE_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct _queue_node QueueNode; 

typedef struct _my_queue MyQueue;

MyQueue* createQueue();

QueueNode* newNode(int value);

int get_size(MyQueue* queue);

void free_queue(MyQueue* queue);

void push_back(MyQueue* queue, int value);

int pop_front(MyQueue* queue);

MyQueue* join(MyQueue* q1, MyQueue* q2);

MyQueue* copy_queue(MyQueue* queue);

void print_queue(MyQueue* queue);

MyQueue* quick_sort(MyQueue* queue);

#endif