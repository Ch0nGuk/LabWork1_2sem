#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polynomial.h"
#include "field_info.h"

Polynomial* CreatePolynomial(FieldInfo* FInfo, int degree) {

    if (degree < 0) return NULL;

    Polynomial* poly = (Polynomial*)malloc(sizeof(Polynomial));

    if (poly == NULL) {
        return NULL;
    }

    poly->polynomial_type = FInfo;
    poly->degree = degree;

    poly->coefficients = (void*)malloc(FInfo->size * (poly->degree + 1));

    if (poly->coefficients == NULL) {
        free(poly);
        return NULL;
    }

    memset(poly->coefficients, 0, FInfo->size * poly->degree + 1);

    return poly;

}

void FreePolynomial(Polynomial* poly) {

    if (poly == NULL) {
        return;
    }
    
    if (poly->coefficients != NULL) {
        free(poly->coefficients);
    }

    free(poly);

}

static void* GetCoeffPtr(Polynomial* poly, int index) {

    if (poly == NULL || index < 0 || index >= (int)poly->degree + 1) {
        return NULL;
    }

    return (char*)poly->coefficients + (index * poly->polynomial_type->size);

}

void SetCoeff(Polynomial* poly, int index, void* src) {

    void* target = GetCoeffPtr(poly, index);

    if (target != NULL && src != NULL) {
        memcpy(target, src, poly->polynomial_type->size);
    }

}

void PrintPolynomial(Polynomial* poly) {

    if (poly == NULL) {
        return;
    }

    for (int degree = (int)poly->degree; degree >= 0; degree--) {
        void* coeff_adress = GetCoeffPtr(poly, degree);
        poly->polynomial_type->print(coeff_adress);

        if (degree > 1) {
            printf("*x^%d + ", degree);
        } else if (degree == 1) {
            printf("*x + ");
        }
    }
    
}

void EvaluatePolynomial(Polynomial* poly, void* dot, void* result) {

    if (poly == NULL || dot == NULL || result == NULL) {
        return;
    }

    void* senior_coeff = GetCoeffPtr(poly, poly->degree);
    memcpy(result, senior_coeff, poly->polynomial_type->size);

    for (int degree = (int)poly->degree - 1; degree >= 0; degree--) {
        poly->polynomial_type->mult(result, dot, result);
        void* current_coeff = GetCoeffPtr(poly, degree);
        poly->polynomial_type->add(result, current_coeff, result);
    }

}

void AddPolynomial(Polynomial* poly1, Polynomial* poly2, Polynomial* result_poly) {

    if (poly1->polynomial_type != poly2->polynomial_type || poly1->polynomial_type != result_poly->polynomial_type) return;

    void* temp_sum = malloc(poly1->polynomial_type->size);

    if (temp_sum == NULL) {
        return;
    }

    int result_degree = poly1->degree >= poly2->degree ? (int)poly1->degree : (int)poly2->degree;

    for (int degree = result_degree; degree >= 0; degree--) {
        void* coef1 = GetCoeffPtr(poly1, degree);
        void* coef2 = GetCoeffPtr(poly2, degree);

        if (coef1 != NULL && coef2 != NULL) {
            poly1->polynomial_type->add(coef1, coef2, temp_sum);
        } else if (coef2 == NULL) {
            memcpy(temp_sum, coef1, poly1->polynomial_type->size);
        } else if (coef1 == NULL) {
            memcpy(temp_sum, coef2, poly2->polynomial_type->size);
        }

        SetCoeff(result_poly, degree, temp_sum);
    }

    free(temp_sum);

}

void MultScalar(Polynomial* poly, void* scalar) {

    if (poly == NULL || scalar == NULL) {
        return;
    }

    for (int degree = (int)poly->degree; degree >= 0; degree--) {
        void* coef = GetCoeffPtr(poly, degree);
        poly->polynomial_type->mult(coef, scalar, coef);
    }

}

void PolynomialMult(Polynomial* poly1, Polynomial* poly2, Polynomial* result_poly) {

    if (poly1->polynomial_type != poly2->polynomial_type || poly1->polynomial_type != result_poly->polynomial_type) return;

    if (poly1 == NULL || poly2 == NULL || result_poly == NULL) {
        return;
    }

    if (result_poly->degree + 1 < poly1->degree + poly2->degree) {
        return;
    }

    void* new_coef = malloc(result_poly->polynomial_type->size);

    if (new_coef == NULL) {
        return;
    }

    memset(result_poly->coefficients, 0, result_poly->polynomial_type->size * (result_poly->degree + 1));

    for (int degree1 = (int)poly1->degree; degree1 >= 0; degree1--) {
        for (int degree2 = (int)poly2->degree; degree2 >= 0; degree2--) {   
            int result_degree = degree1 + degree2;
            void* coef1 = GetCoeffPtr(poly1, degree1);
            void* coef2 = GetCoeffPtr(poly2, degree2);

            poly1->polynomial_type->mult(coef1, coef2, new_coef);
            result_poly->polynomial_type->add(new_coef, GetCoeffPtr(result_poly, result_degree), new_coef);
            SetCoeff(result_poly, result_degree, new_coef);
        }
    }

    free(new_coef);

}


Polynomial* DerivativeOfPolynomial(Polynomial* poly)
{
    if (poly == NULL) return NULL;
    
    if (poly->degree == 0)
    {
        Polynomial* diff_poly = CreatePolynomial(poly->polynomial_type, 0);
        // void* src = malloc(poly->polynomial_type->size);

        // if (src == NULL) return NULL;

        // void* coeff = GetCoeffPtr(poly, 0);
        // poly->polynomial_type->DerivativeOperationInCoef(coeff, 0, src);
        // SetCoeff(diff_poly, 0, src);

        // free(src);

        return diff_poly;
    }

    Polynomial* diff_poly = CreatePolynomial(poly->polynomial_type, poly->degree - 1);

    void* diff_coeff = malloc(poly->polynomial_type->size);
    if (diff_coeff == NULL) return NULL;

    for (int degree = poly->degree; degree > 0; degree--)
    {
        void* tmp_coeff = GetCoeffPtr(poly, degree);

        diff_poly->polynomial_type->derivop(tmp_coeff, degree, diff_coeff);

        SetCoeff(diff_poly, degree - 1, diff_coeff);
    }

    free(diff_coeff);

    return diff_poly;

}