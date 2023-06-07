#include "linlist2.h"

void initList(LinearList* list) {
    list->elements = (NodeArray)calloc(MAX_SIZE, sizeof(Node));
    list->size = 0;
}

size_t getSize(LinearList* list)
{
    if (list == NULL) return 0;
    return list->size;
}

void insertElement(LinearList* list, Iterator iterator, Complex data) {
    if (list == NULL) return;
    if (iterator < 0 || iterator > list->size) {
        fprintf(stderr, "Error: Invalid iterator.\n");
        return;
    }
    if (list->size == MAX_SIZE) {
        fprintf(stderr, "Error: List is full, cannot insert element.\n");
        return;
    }

    // Сдвигаем элементы вправо, начиная с конца списка
    for (int i = list->size; i > iterator; i--) {
        list->elements[i] = list->elements[i - 1];
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->elements[iterator + 1];
    newNode->prev = list->elements[iterator - 1];
    // Вставляем новый элемент на указанную позицию
    list->elements[iterator] = newNode;
    list->size++;
}

void removeElement(LinearList* list, Iterator iterator) {
    if (list == NULL) return;
    if (iterator < 0 || iterator >= list->size) {
        fprintf(stderr, "Error: Invalid iterator.\n");
        return;
    }
    Node* node = list->elements[iterator];
    Node* prev = node->prev;
    Node* next = node->next;
    prev->next = node->next;
    next->prev = node->prev;
    free(node);
    // Сдвигаем элементы влево, начиная с позиции iterator
    for (int i = iterator; i < list->size - 1; i++) {
        list->elements[i] = list->elements[i + 1];
    }
    list->size--;
}

void printList(LinearList* list) {
    if (list == NULL) return;
    for (int i = 0; i < list->size; i++) {
        double real = list->elements[i]->data.real;
        double imag = list->elements[i]->data.imaginary;
        if (imag >= 0) {
            printf("[%.1lf + %.1lf*i]\n", real, imag);
        }
        else {
            printf("[%.1lf - %.1lf*i]\n", real, -imag);
        }
    }
}

void destroyList(LinearList* list)
{
    if (list == NULL) return;
    free(list->elements);
    return;
}

void removeEveryKthElement(LinearList* list, size_t k)
{
    if (list == NULL) return;
    if (k <= 0 || k > list->size) {
        fprintf(stderr, "Error: Inappropriate step.\n");
        return;
    }
    for (size_t i = 1; i <= getSize(list); i *= k) {
        removeElement(list, i);
    }
    return;
}