#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "field_info.h"

static FieldInfo* int_field_info_ptr = NULL;
static FieldInfo* complex_field_info_ptr = NULL;

static char* strip_str(char* str)
{
    char* end;
    while (isspace((unsigned char)*str)) str++; 

    if (*str == 0) return str; 

    end = str + strlen(str) - 1; 
    while (end > str && isspace((unsigned char)*end)) end--; 
    end[1] = '\0'; 

    return str;
}

int read_num(void* str, NumType type)
{
    char buffer[256]; 
    char* endstr; 
    char* clean_str; 

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return 0;

    clean_str = strip_str(buffer);
    
    if (strlen(clean_str) == 0) return 0;

    if (type == INT_TYPE)
    {
        int value = strtol(clean_str, &endstr, 10); 
        if (*endstr != '\0') return 0; 
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
    return read_num(ptr, INT_TYPE);
}

static int complex_read(void* str)
{
    Complex* ptr = (Complex*)str;
    return (read_num(&(ptr->re), DOUBLE_TYPE) && read_num(&(ptr->im), DOUBLE_TYPE));
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

FieldInfo* get_int_field_info() {
    if (int_field_info_ptr == NULL) {
        int_field_info_ptr = (FieldInfo*)malloc(sizeof(FieldInfo));
        int_field_info_ptr->add = int_add;
        int_field_info_ptr->mult = int_mul;
        int_field_info_ptr->print = int_print;
        int_field_info_ptr->read = int_read;
        int_field_info_ptr->derivop = int_derivative_operation; 
        int_field_info_ptr->size = sizeof(int);
    }
    return int_field_info_ptr;
}

FieldInfo* get_complex_field_info() {
    if (complex_field_info_ptr == NULL) {
        complex_field_info_ptr = (FieldInfo*)malloc(sizeof(FieldInfo));
        complex_field_info_ptr->add = complex_add;
        complex_field_info_ptr->mult = complex_mult;
        complex_field_info_ptr->print = complex_print;
        complex_field_info_ptr->read = complex_read;
        complex_field_info_ptr->derivop = complex_derivative_operation;
        complex_field_info_ptr->size = sizeof(Complex);
    }
    return complex_field_info_ptr;
}