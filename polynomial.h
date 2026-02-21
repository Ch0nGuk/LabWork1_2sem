#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include "field_info.h"

typedef struct Polynomial
{
    FieldInfo* polynomial_type;
    void* coefficients;
    size_t count;
} Polynomial;

Polynomial* CreatePolynomial(FieldInfo* FInfo, int degree);
void FreePolynomial(Polynomial* Poly);
void* GetCoeffPtr(Polynomial* poly, int index);
void SetCoeff(Polynomial* poly, int index, void* src);
void PrintPolynomial(Polynomial* poly);
void EvaluatePolynomial(Polynomial* poly, void* dot, void* result);
void AddPolynomial(Polynomial* poly1, Polynomial* poly2, Polynomial* result_poly);
void ScalarMult(Polynomial* poly, void* scalar);
void PolynomialMult(Polynomial* poly1, Polynomial* poly2, Polynomial* result_poly);

#endif // POLYNOMIAL_H