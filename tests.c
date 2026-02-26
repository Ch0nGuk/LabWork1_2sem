#include <stdio.h>
#include <stdlib.h>
#include "field_info.h"
#include "polynomial.h"

void tests()
{
    FieldInfo* IntField = GetIntFieldInfo();
    FieldInfo* ComplexField = GetComplexFieldInfo();

    printf("\n=== POLYNOMIAL TESTS ===\n\n");

    // Целые числа (Сложение и вычисление) ---
    printf("[Test 1: Integer Polynomials]\n");
    
    // P1(x) = 2x + 5 
    Polynomial* p1 = CreatePolynomial(IntField, 1);
    int c1_1 = 2, c1_0 = 5;
    SetCoeff(p1, 1, &c1_1);
    SetCoeff(p1, 0, &c1_0);
    printf("P1: "); PrintPolynomial(p1);

    // P2(x) = 1x^2 + 3 
    Polynomial* p2 = CreatePolynomial(IntField, 2);
    int c2_2 = 1, c2_0 = 3;
    SetCoeff(p2, 2, &c2_2);
    SetCoeff(p2, 0, &c2_0);
    printf("P2: "); PrintPolynomial(p2);

    // Сложение: P3 = P1 + P2 = x^2 + 2x + 8
    Polynomial* p3 = CreatePolynomial(IntField, 2);
    AddPolynomial(p1, p2, p3);
    printf("P1 + P2 = "); PrintPolynomial(p3);

    // Вычисление P1(3) 
    int x_val = 3, res_val = 0;
    EvaluatePolynomial(p1, &x_val, &res_val);
    printf("Value of P1 at x=3: %d (Expected: 11)\n", res_val);
    assert(res_val == 11);

    printf("---------------------------------\n");

    // Комплексные числа (Умножение) ---
    printf("[Test 2: Complex Polynomials]\n");

    // C1(x) = (1 + 2i)x + (3 + 0i)
    Polynomial* c1 = CreatePolynomial(ComplexField, 1);
    Complex v1_1 = {1.0, 2.0}, v1_0 = {3.0, 0.0};
    SetCoeff(c1, 1, &v1_1);
    SetCoeff(c1, 0, &v1_0);
    printf("C1: "); PrintPolynomial(c1);

    // Умножение на скаляр 
    Polynomial* c2 = CreatePolynomial(ComplexField, 1);
    double scalar = 2.0;
    PolynomialMultByScalar(c1, &scalar, c2);
    printf("C1 * 2.0 = "); PrintPolynomial(c2);

    // Умножение двух многочленов (C1 * C1)
    Polynomial* c_res = CreatePolynomial(ComplexField, 2);
    PolynomialMult(c1, c1, c_res);
    printf("C1 * C1 = "); PrintPolynomial(c_res);

    printf("---------------------------------\n");

    FreePolynomial(p1);
    FreePolynomial(p2);
    FreePolynomial(p3);
    FreePolynomial(c1);
    FreePolynomial(c2);
    FreePolynomial(c_res);

    printf("Succesfull completed tests\n");
}