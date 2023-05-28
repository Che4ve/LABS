#ifndef __LINLIST_H__
#define __LINLIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double real;
    double imaginary;
} Complex;

#define MAX_SIZE 200 // Максимальный размер списка

typedef struct {
    Complex* elements; // Массив элементов
    size_t size; // Размер списка (без учета барьерного элемента)
} LinearList;

typedef size_t Iterator; // Итератор - индекс элемента в массиве

void initList(LinearList* list);

size_t getSize(LinearList* list);

void insertElement(LinearList* list, Iterator iterator, Complex element);

void removeElement(LinearList* list, Iterator iterator);

void printList(LinearList* list);

void destroyList(LinearList* list);

void removeEveryKthElement(LinearList* list, size_t k);

#endif