#include <stdio.h>
#include <ctype.h>
#include <limits.h> // Библиотека, содержащая INT_MAX

int main() {
    
    int c; // Переменная, которая будет хранить код символа
    
    long long number = -1; // Положительное число ("-1" - флаг того, что число не в процессе записи)
    int num_digit = 0; // Количество разрядов в числе
     
    while (1) {
        
        c = getchar(); // Берём символ, поступивший на вход
        
        if (c == EOF) break; // Условие выхода из цикла
        
        if (isdigit(c)) { // Если символ - цифра
            
            if (number == -1) { // Если число не начало записываться до этого
                number = 0;
            }
            
            number = number * 10 + (c - '0'); // Составляем число из цифр
            num_digit += 1; // Прибавляем разряд числа
            
        } else if (isspace(c)) { // Если символ - пробел
            
            if (number == 0) {
                for (int i = 1; i <= num_digit; i++) { // Вывод подряд идущих нулей
                    printf("%d", 0);
                }
            } else if ((number <= INT_MAX) && (number != -1) && (num_digit <= 10)) { // Если число не превышает INT_MAX
                printf("%lld", number);
            }
            
            putchar(c); // Ставим знак пробела
            
            number = -1; // Запись числа остановилась
            num_digit = 0; // Обнуляем число разрядов

        } else { // Если символ - другой
            
            if ((number != -1)) {
                printf("%lld", number); // Выводим число в составе недесятичного
            }
            
            putchar(c); // Печаем символ, поступивший на вход
            
            number = -1; // Останавливаем запись числа
            num_digit = 0; // Обнуляем число разрядов
        }
    }
    
    return 0;
}

