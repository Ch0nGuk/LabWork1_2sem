#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "polynomial.h"
#include "tools.h"



static char* strip_str(char* str)
{
    char* end;

    while ( isspace((unsigned char)*str) ) str++; // прибавлякем начало строки, пока не пройдем все пробелы, табы и тп

    if (*str == 0) return str; //строка состоит только из пробелов

    end = str + strlen(str) - 1; // ставим указатель end на конец и вычитаем один, чтобы избавиться от \0

    while ( end > str && isspace((unsigned char)*end) ) end--; 
    end[1] = '\0'; // ставим терминатор строки

    return str;

}


int read_num(void* str, NumType type)
{
    char buffer[256]; // буффер
    char* endstr; // указатель куда будет писаться первые несчитанные элементы после strtol && strtod
    char* clean_str; // начало чистой строки

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return 0;

    clean_str = strip_str(buffer);
    
    if (strlen(clean_str) == 0) return 0;

    if (type == INT_TYPE)
    {

        int value = strtol(clean_str, &endstr, 10); // передаем строку, адрес указателя в который запишется адрес конца строки, основание системы счисления
        if (*endstr != '\0') return 0; // значит после числа есть какой-то мусор (буквы, точки и тп) => ввод не корректен
        *(int*)str = value;

        return 1;

    }

    if (type == DOUBLE_TYPE)
    {

        double value = strtod(clean_str, &endstr);
        if (*endstr != '\0') return 0;
        *(double*)str = value;

        return 1;

    }

    return 0;

}


void PrintListOfPolynomials(Polynomial* arr[], int count_polys)
{
    for (int number = 0; number < count_polys; number++)
    {
        printf("%d.  ", number + 1);
        PrintPolynomial(arr[number]);
        printf("\n");
    }
}