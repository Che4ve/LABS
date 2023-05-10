#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>

#define VOWELS (1u << ('a' - 'a') | \
                1u << ('e' - 'a') | \
                1u << ('i' - 'a') | \
                1u << ('o' - 'a') | \
                1u << ('u' - 'a') | \
                1u << ('y' - 'a'))   // Составляем множество гласных

int main() {

    int32_t c; // Переменная, отвечающая за код входного символа
    
    bool has_one_vowel = false; // (Флаг) Имеет ли слово ровно одну гласную
    bool correct_word = false;
    bool answer = true;
    
    while (1) { // Пока ввод не достиг конца файла
        c = getchar();
        
        if (isalpha(c)) { // Если "с" - буква
            c = tolower(c); // Переводим букву в нижний регистр
            int32_t symbol = 1u << (c - 'a'); // Записываем символ в битовую маску

            if (symbol & VOWELS) {
                if (!has_one_vowel) {
                    has_one_vowel = true;
                    correct_word = true;
                } else {
                    correct_word = false;
                }
            }
            
        } else if ((isspace(c)) || (c == EOF)) { // Если "с" - разделительный знак
            answer &= correct_word;
            has_one_vowel = false;
        }
        
        if (c == EOF) break;
    }

    if (answer) {
        printf("\nYES\n");
    } else {
        printf("\nNO\n");
    }
    
    return 0;
}

