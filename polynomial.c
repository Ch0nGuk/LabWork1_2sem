#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"
#include "field_info.h"
#include <string.h>


Polynomial* CreatePolynomial(FieldInfo* FInfo, int degree)
{
    Polynomial* poly = (Polynomial*)malloc(sizeof(Polynomial));
    if (poly == NULL) return NULL;

    poly->polynomial_type = FInfo;

    poly->count = (size_t)(degree + 1);

    poly->coefficients = (void*)malloc(FInfo->size * poly->count);
    if (poly->coefficients == NULL)
    {
        free(poly);
        return NULL;
    }

    memset(poly->coefficients, 0, FInfo->size * poly->count);

    return poly;
}

void FreePolynomial(Polynomial* poly)
{
    if (poly == NULL) return;
    
    if (poly->coefficients != NULL) free(poly->coefficients);
    free(poly);
}

void* GetCoeffPtr(Polynomial* poly, int index)
{
    if (poly == NULL || index < 0 || index >= (int)poly->count) return NULL;
    return (char*)poly->coefficients + (index * poly->polynomial_type->size);
}

void SetCoeff(Polynomial* poly, int index, void* src)
{
    void* target = GetCoeffPtr(poly, index);
    if (target != NULL && src != NULL)
    {
        memcpy(target, src, poly->polynomial_type->size);
    }
}

void PrintPolynomial(Polynomial* poly)
{
    if (poly == NULL) return;
    printf("Polynomial (degree %zu):\t", poly->count - 1);

    for (int degree = (int)poly->count - 1; degree >= 0; degree--)
    {
        void* coeff_adress = GetCoeffPtr(poly, degree);
        poly->polynomial_type->print(coeff_adress);

        if (degree > 1)
        {
            printf("*x^%d + ", degree);
        }

        else if (degree == 1)
        {
            printf("*x + ");
        }
    }
    printf("\n");
}


void EvaluatePolynomial(Polynomial* poly, void* dot, void* result)
{
    if (poly == NULL || dot == NULL || result == NULL) return;
    void* senior_coeff = GetCoeffPtr(poly, poly->count - 1);
    memcpy(result, senior_coeff, poly->polynomial_type->size);
    for (int degree = (int)poly->count - 2; degree >= 0; degree--)
    {
        poly->polynomial_type->mult(result, dot, result);
        void* current_coeff = GetCoeffPtr(poly, degree);
        poly->polynomial_type->add(result, current_coeff, result);
    }
}