// М8О-104Б-22 Чесноков Василий; ЛР 15 - Задание 3
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define INF 1e9

void swap(int *a, int *b) { // Процедура взаимной перестановки двух переменных
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int matrix[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0 ,0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0}};

    int prefix_sum[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // Массив преф. сумм столбцов

    int n = 0;

    printf("Please, enter the size of the square matrix (one number): ");
    scanf("%d", &n);

    int j_max = 0; // Индекс максиsмального столбца
    int j_min = 0; // Индекс минимального столбца

    int max_sum = -INF;
    int min_sum = INF;

    int elem; // Входное значение (элемент)

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &elem) > 0) {
                matrix[i][j] = elem;
                prefix_sum[j] += elem;
            } else {
                break;
            }
        }
    }

    // while (scanf("%d", &elem) != EOF) {
    //     matrix[n][m] = elem;
    //     prefix_sum[m] += elem;

    //     m++;

    //     if (getc(stdin) == '\n') { // Если на вход поступил Enter
    //         n++;
    //         m = 0;
    //     }  
    // }
    
    for (int k = 0; k < n; k++) { 
        if (prefix_sum[k] > max_sum) { // Если максимальный столбец
            max_sum = prefix_sum[k];
            j_max = k;
        } 
        if (prefix_sum[k] < min_sum) { // Если минимальный столбец
            min_sum = prefix_sum[k];
            j_min = k;
        }
    }

    // Теперь n - ранг матрицы
    if (n > 8) n = 8;

    printf("\n");
    for (int x = 0; x < n; x++) {
        swap(&matrix[x][j_min], &matrix[x][j_max]); // Перестановка макс. и мин. столбцов
        for (int y = 0; y < n; y++) {
            printf("%d ", matrix[x][y]); // Вывод элемента матрицы
        }
        printf("\n");
    }

    // Вывод информации о перестановке (необязательно)
    if ((j_min != j_max) && (min_sum != max_sum)) { // Если есть разные по сумме столбцы
        printf("Columns %d and %d were swapped\n", j_min + 1, j_max + 1);
    } 

    return 0;
}
