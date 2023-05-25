#include "linlist.h"

void initList(LinearList* list) {
    list->elements = malloc(MAX_SIZE * sizeof(Complex));
    list->size = 0;
}

size_t getSize(LinearList* list)
{
    if (list == NULL) return 0;
    return list->size;
}

void insertElement(LinearList* list, Iterator iterator, Complex element) {
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

    // Вставляем новый элемент на указанную позицию
    list->elements[iterator] = element;
    list->size++;
}

void removeElement(LinearList* list, Iterator iterator) {
    if (list == NULL) return;
    if (iterator < 0 || iterator >= list->size) {
        fprintf(stderr, "Error: Invalid iterator.\n");
        return;
    }

    // Сдвигаем элементы влево, начиная с позиции iterator
    for (int i = iterator; i < list->size - 1; i++) {
        list->elements[i] = list->elements[i + 1];
    }

    list->size--;
}

void printList(LinearList* list) {
    if (list == NULL) return;
    for (int i = 0; i < list->size; i++) {
        double real = list->elements[i].real;
        double imag = list->elements[i].imaginary;
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