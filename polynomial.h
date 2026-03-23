#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "field_info.h"

typedef struct Polynomial {
    FieldInfo* polynomial_type;
    void* coefficients;
    int degree;
} Polynomial;

Polynomial* create_polynomial(FieldInfo* f_info, int degree);

void free_polynomial(Polynomial* poly);
void set_coeff(Polynomial* poly, int index, void* src);
void print_polynomial(Polynomial* poly);
void evaluate_polynomial(Polynomial* poly, void* dot, void* result);
void add_polynomial(Polynomial* poly1, Polynomial* poly2, Polynomial* result_poly);
void mult_scalar(Polynomial* poly, void* scalar);
void mult_polynomial(Polynomial* poly1, Polynomial* poly2, Polynomial* result_poly);

Polynomial* derivative_of_polynomial(Polynomial* poly);

#endif // POLYNOMIAL_H