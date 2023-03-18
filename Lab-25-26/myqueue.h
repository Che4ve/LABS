#ifndef __MYQUEUE_H__
#define __MYQUEUE_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct _queue_node QueueNode;

typedef struct _my_queue MyQueue;

MyQueue* createQueue();

QueueNode* newNode(int value);

void push_back(MyQueue* queue, QueueNode* node);

void pop_front(MyQueue* queue);

MyQueue* join(MyQueue* q1, MyQueue* q2);

void print_queue(MyQueue* queue);

MyQueue* quick_sort(MyQueue* queue);

#endif