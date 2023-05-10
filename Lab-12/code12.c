#include <stdio.h>

long long delete_even(long long x) { // Функция перезаписи числа без чётных чисел
    long long res = 0;
    long long num_digit = 1; // Десять в нулевой степени
    
    while (x != 0) {
        if (x & 1) { // Если x - чётное
            res = res + ((x % 10) * num_digit); // Добавляем к результату цифру, умноженную на десять в степени
            num_digit *= 10; // Повышаем степень десяти
        }
        x /= 10; // Убираем последнюю цифру
    }
    return res;
}

int main() {
    long long a;
    
    while (scanf("%lld", &a) != EOF) { // Пока ввод - не конец файла (и записываем ввод в "a")
        if (delete_even(a) != 0) { // Если в числе не все цифры - чётные
            printf("%lld ", delete_even(a)); // Печатаем результат
        } else {
            printf(""); // Ничего не печатается
        }
    }
}
