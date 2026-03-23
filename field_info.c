#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "field_info.h"

static FieldInfo* INT_FIELD_INFO = NULL;
static FieldInfo* COMPLEX_FIELD_INFO = NULL;

static char* StripStr(char* str)
// Функция, которая "раздевает" строку, то есть убирает у нее все пробелы, табы в начале и конце
{
    char* end;

    while ( isspace((unsigned char)*str) ) str++; // прибавлякем начало строки, пока не пройдем все пробелы, табы и тп

    if (*str == 0) return str; //строка состоит только из пробелов

    end = str + strlen(str) - 1; // ставим указатель end на конец и вычитаем один, чтобы избавиться от \0

    while ( end > str && isspace((unsigned char)*end) ) end--; 
    end[1] = '\0'; // ставим терминатор строки

    return str;

}


int ReadNum(void* str, NumType type) // ОБЩАЯ ФУНКЦИЯ, которая считывает значение из буфера и сравнивает с типом данных. 
// Возвращает 1 если введенное число и тип данных совпадают, 0 в обратном случае
{
    char buffer[256]; // буффер
    char* endstr; // указатель куда будет писаться первые несчитанные элементы после strtol && strtod
    char* clean_str; // начало чистой строки

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return 0;

    clean_str = StripStr(buffer);
    
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

static void int_add(void* element1, void* element2, void* result) {
    *(int*)result = *(int*)element1 + *(int*)element2;
}

static void int_mul(void* element1, void* element2, void* result) {
    *(int*)result = (*(int*)element1) * (*(int*)element2);
}

static void int_print(void* element) {
    printf("%d", *(int*)element);
}

static void complex_add(void* element1, void* element2, void* result) {
    Complex* res = (Complex*)result;
    Complex* el1 = (Complex*)element1;
    Complex* el2 = (Complex*)element2;

    res->im = el1->im + el2->im;
    res->re = el1->re + el2->re;
}

static void complex_mult(void* element1, void* element2, void* result) {
    Complex* el1 = (Complex*)element1;
    Complex* el2 = (Complex*)element2;
    Complex res_tmp;

    res_tmp.re = (el1->re) * (el2->re) - (el1->im) * (el2->im);
    res_tmp.im = (el1->re) * (el2->im) + (el1->im) * (el2->re);

    *(Complex*)result = res_tmp;
}

static void complex_print(void* element) {
    Complex* el = (Complex*)element;
    printf("(%.2f %c %.2fi)", el->re, (el->im >= 0 ? '+': '-'), fabs(el->im));
}

static int int_read(void* str)
{
    int* ptr = (int*)str;
    return ReadNum(ptr, INT_TYPE);
}

static int complex_read(void* str)
{
    Complex* ptr = (Complex*)str;
    return (ReadNum(&(ptr->re), DOUBLE_TYPE) && ReadNum(&(ptr->im), DOUBLE_TYPE));
}

static void complex_derivative_operation(void* co, int degree, void* result)
{

    Complex* coeff = (Complex*)co;
    Complex* res = (Complex*)result;
    res->re = coeff->re * degree;
    res->im = coeff->im * degree;

}

static void int_derivative_operation(void* co, int degree, void* result)
{

    int* coeff = (int*)co;
    int* res = (int*)result;

    *res = *coeff * degree;

}


FieldInfo* GetIntFieldInfo() {

    if (INT_FIELD_INFO == NULL) {
        INT_FIELD_INFO = (FieldInfo*)malloc(sizeof(FieldInfo));

        INT_FIELD_INFO->add = int_add;
        INT_FIELD_INFO->mult = int_mul;
        INT_FIELD_INFO->print = int_print;
        INT_FIELD_INFO->read = int_read;
        INT_FIELD_INFO->derivop = int_derivative_operation; 
        INT_FIELD_INFO->size = sizeof(int);
    }

    return INT_FIELD_INFO;
}

FieldInfo* GetComplexFieldInfo() {

    if (COMPLEX_FIELD_INFO == NULL) {
        COMPLEX_FIELD_INFO = (FieldInfo*)malloc(sizeof(FieldInfo));

        COMPLEX_FIELD_INFO->add = complex_add;
        COMPLEX_FIELD_INFO->mult = complex_mult;
        COMPLEX_FIELD_INFO->print = complex_print;
        COMPLEX_FIELD_INFO->read = complex_read;
        COMPLEX_FIELD_INFO->derivop = complex_derivative_operation;
        COMPLEX_FIELD_INFO->size = sizeof(Complex);
    }

    return COMPLEX_FIELD_INFO;
}

