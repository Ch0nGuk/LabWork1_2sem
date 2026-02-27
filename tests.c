#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "polynomial.h"
#include "field_info.h"

// Макрос для получения доступа к коэффициенту по индексу через void*
#define GET_COEFF(poly, index) ((char*)(poly)->coefficients + (index) * (poly)->polynomial_type->size)

//  ТЕСТЫ ДЛЯ INT 
void test_int() {
    printf("\n=== STARTING INT TESTS ===\n");
    FieldInfo* IntField = GetIntFieldInfo();

    // 1. Создание и вычисление
    // P1 = 2x + 3
    Polynomial* p1 = CreatePolynomial(IntField, 1);
    int c3 = 3, c2 = 2;
    SetCoeff(p1, 0, &c3);
    SetCoeff(p1, 1, &c2);
    
    int res_eval;
    int x_val = 2;
    EvaluatePolynomial(p1, &x_val, &res_eval);
    
    printf("Evaluating: P1 = "); PrintPolynomial(p1);
    printf(" at x = %d. Result: %d\n", x_val, res_eval);
    assert(res_eval == 7);

    // 2. Сложение
    // P2 = 1x + 1
    Polynomial* p2 = CreatePolynomial(IntField, 1);
    int c1 = 1;
    SetCoeff(p2, 0, &c1);
    SetCoeff(p2, 1, &c1);
    
    Polynomial* p_sum = CreatePolynomial(IntField, 1);
    AddPolynomial(p1, p2, p_sum);
    
    printf("Addition: ("); PrintPolynomial(p1);
    printf(") + ("); PrintPolynomial(p2);
    printf(") == "); PrintPolynomial(p_sum); printf("\n");
    
    assert(*(int*)GET_COEFF(p_sum, 1) == 3);
    assert(*(int*)GET_COEFF(p_sum, 0) == 4);

    // 3. Умножение
    // (2x + 3) * (1x + 1) = 2x^2 + 5x + 3
    Polynomial* p_mult = CreatePolynomial(IntField, 2);
    PolynomialMult(p1, p2, p_mult);
    
    printf("Multiplication: ("); PrintPolynomial(p1);
    printf(") * ("); PrintPolynomial(p2);
    printf(") == "); PrintPolynomial(p_mult); printf("\n");
    
    assert(*(int*)GET_COEFF(p_mult, 2) == 2);
    assert(*(int*)GET_COEFF(p_mult, 1) == 5);
    assert(*(int*)GET_COEFF(p_mult, 0) == 3);

    // 4. Производная
    // (2x + 3)' = 2
    Polynomial* p_der = DerivativeOfPolynomial(p1);
    
    printf("Derivative: ("); PrintPolynomial(p1);
    printf(")' == "); PrintPolynomial(p_der); printf("\n");
    
    assert(p_der->count == 1);
    assert(*(int*)GET_COEFF(p_der, 0) == 2);

    FreePolynomial(p1);
    FreePolynomial(p2);
    FreePolynomial(p_sum);
    FreePolynomial(p_mult);
    FreePolynomial(p_der);
    printf("--- INT tests PASSED ---\n");
}

//  ТЕСТЫ ДЛЯ COMPLEX 
void test_complex() {
    printf("\n=== STARTING COMPLEX TESTS ===\n");
    FieldInfo* ComplexField = GetComplexFieldInfo();

    // 1. Создание и вычисление
    // P1 = (1+1i)x + (2+0i)
    Polynomial* p1 = CreatePolynomial(ComplexField, 1);
    Complex c2_0 = {2.0, 0.0};
    Complex c1_1 = {1.0, 1.0};
    SetCoeff(p1, 0, &c2_0);
    SetCoeff(p1, 1, &c1_1);
    
    Complex res_eval;
    Complex x_val = {2.0, 0.0};
    EvaluatePolynomial(p1, &x_val, &res_eval);
    
    printf("Evaluating: P1 = "); PrintPolynomial(p1);
    printf("\n at x = "); ComplexField->print(&x_val);
    printf(". Result: "); ComplexField->print(&res_eval); printf("\n");
    
    assert(res_eval.re == 4.0 && res_eval.im == 2.0);

    // 2. Сложение
    // P2 = (0+1i)x + (1+0i)
    Polynomial* p2 = CreatePolynomial(ComplexField, 1);
    Complex c1_0 = {1.0, 0.0};
    Complex c0_1 = {0.0, 1.0};
    SetCoeff(p2, 0, &c1_0);
    SetCoeff(p2, 1, &c0_1);
    
    Polynomial* p_sum = CreatePolynomial(ComplexField, 1);
    AddPolynomial(p1, p2, p_sum);
    
    printf("Addition: ("); PrintPolynomial(p1);
    printf(") + ("); PrintPolynomial(p2);
    printf(") == "); PrintPolynomial(p_sum); printf("\n");
    
    Complex* r_sum1 = (Complex*)GET_COEFF(p_sum, 1);
    Complex* r_sum0 = (Complex*)GET_COEFF(p_sum, 0);
    assert(r_sum1->re == 1.0 && r_sum1->im == 2.0);
    assert(r_sum0->re == 3.0 && r_sum0->im == 0.0);

    // 3. Умножение
    // P1 * P2 = (-1+i)x^2 + (1+3i)x + 2
    Polynomial* p_mult = CreatePolynomial(ComplexField, 2);
    PolynomialMult(p1, p2, p_mult);
    
    printf("Multiplication: ("); PrintPolynomial(p1);
    printf(") * ("); PrintPolynomial(p2);
    printf(") == "); PrintPolynomial(p_mult); printf("\n");
    
    Complex* m2 = (Complex*)GET_COEFF(p_mult, 2);
    Complex* m1 = (Complex*)GET_COEFF(p_mult, 1);
    Complex* m0 = (Complex*)GET_COEFF(p_mult, 0);
    assert(m2->re == -1.0 && m2->im == 1.0);
    assert(m1->re == 1.0 && m1->im == 3.0);
    assert(m0->re == 2.0 && m0->im == 0.0);

    // 4. Производная
    // ((1+i)x + 2)' = 1+i
    Polynomial* p_der = DerivativeOfPolynomial(p1);
    
    printf("Derivative: ("); PrintPolynomial(p1);
    printf(")' == "); PrintPolynomial(p_der); printf("\n");
    
    Complex* d0 = (Complex*)GET_COEFF(p_der, 0);
    assert(d0->re == 1.0 && d0->im == 1.0);

    FreePolynomial(p1);
    FreePolynomial(p2);
    FreePolynomial(p_sum);
    FreePolynomial(p_mult);
    FreePolynomial(p_der);
    printf("--- COMPLEX tests PASSED ---\n");
}


