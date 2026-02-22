#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "field_info.h"

static FieldInfo* INT_FIELD_INFO = NULL;
static FieldInfo* COMPLEX_FIELD_INFO = NULL;

void int_add(void* element1, void* element2, void* result) {
    *(int*)result = *(int*)element1 + *(int*)element2;
}

void int_mul(void* element1, void* element2, void* result) {
    *(int*)result = (*(int*)element1) * (*(int*)element2);
}

void int_print(void* element) {
    printf("%d", *(int*)element);
}

void complex_add(void* element1, void* element2, void* result) {
    Complex* res = (Complex*)result;
    Complex* el1 = (Complex*)element1;
    Complex* el2 = (Complex*)element2;

    res->im = el1->im + el2->im;
    res->re = el1->re + el2->re;
}

void complex_mult(void* element1, void* element2, void* result) {
    Complex* el1 = (Complex*)element1;
    Complex* el2 = (Complex*)element2;
    Complex res_tmp;

    res_tmp.re = (el1->re) * (el2->re) - (el1->im) * (el2->im);
    res_tmp.im = (el1->re) * (el2->im) + (el1->im) * (el2->re);

    *(Complex*)result = res_tmp;
}

void complex_print(void* element) {
    Complex* el = (Complex*)element;
    printf("(%.2f %c %.2fi)", el->re, (el->im >= 0 ? '+': '-'), fabs(el->im));
}

FieldInfo* GetIntFieldInfo() {

    if (INT_FIELD_INFO == NULL) {
        INT_FIELD_INFO = (FieldInfo*)malloc(sizeof(FieldInfo));

        INT_FIELD_INFO->add = int_add;
        INT_FIELD_INFO->mult = int_mul;
        INT_FIELD_INFO->print = int_print;
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
        COMPLEX_FIELD_INFO->size = sizeof(Complex);
    }

    return COMPLEX_FIELD_INFO;
}