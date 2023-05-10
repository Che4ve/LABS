#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

void linear_print(int (*matrix)[7], int size, int corner) { // Рекурсивная процедура
    // Передается указатель на двумерный массив, размер матрицы и индекс начала обхода
    if (size <= 0) { // Условие выхода из рекурсии
        return;
    }
    printf("\nsize: %d, corner: (%d, %d)\n", size, corner, corner);
    
    int i = corner - 1; // Индекс начала обхода (i)
    int j = corner - 1; // Индекс начала обхода (j)
    
    for (int k = 1; k < size; k++) { // Цикл обхода правой стенки матрицы
        printf("%d ", *(*(matrix + i) + j));
        i--;
    }
    for (int k = 1; k < size; k++) { // Цикл обхода верхней стенки матрицы
        printf("%d ", *(*(matrix + i) + j));
        j--;
    }
    for (int k = 1; k < size; k++) { // Цикл обхода левой стенки матрицы
        printf("%d ", *(*(matrix + i) + j));
        i++;
    }
    for (int k = 1; k < size; k++) { // Цикл обхода нижней стенки матрицы
        printf("%d ", *(*(matrix + i) + j));
        j++;
    }
    if (size == 1) { // Если ранг равен 1
        printf("%d ", *(*(matrix + i) + j));
    }
    return linear_print(matrix, size - 2, corner - 1); // Рекурсия
}

int main() {

    int matrix[7][7] = {{0, 0, 0, 0, 0, 0, 0}, // Двумерный массив
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0}};
    
    int c; // Знак
    bool is_negative = false; // Если число отрицательное
    
    int elem = 0; // Число

    int i = 0; // Индекс для записи в матрицу (i)
    int j = 0; // Индекс для записи в матрицу (j)
    
    while (1) {
        c = getchar(); // Чтение символа
        
        if (c == '-') { // Если знак минуса
            is_negative = true;
        }
        
        if (isdigit(c)) {
            if (is_negative) {
                elem = elem * 10 - (c - '0'); // Запись отрицательного числа
            } else {
                elem = elem * 10 + (c - '0'); // Запись положительного числа
            }
            
        } else if ((isspace(c)) || c == EOF) { // Если разделительный символ
            matrix[i][j] = elem; // Вносит число в матрицу
            elem = 0; // Обнуляем число
            j++;
            is_negative = false;
            
            if (c == '\n') { // Если 'Enter'
                i++;
                j = 0;
            }
        }
        
        if (c == EOF) break; // Условие завершения цикла
    }
    
    // Теперь i - размер матрицы

//    for (int x = 0; x < i; x++) {
//        for (int y = 0; y < i; y++) {
//            printf("%d ", matrix[x][y]);
//        }
//        printf("\n");
//    }

    linear_print(matrix, i, i); // Процедура вывода линеаризированной матрицы
    printf("\n");
    
    return 0;
}
