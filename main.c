#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"
#include "field_info.h"

void test_int() {
    printf("=== ТЕСТИРОВАНИЕ ТИПА INT ===\n");
    FieldInfo* intField = GetIntFieldInfo();

    // Создаем P1(x) = 1*x + 2
    Polynomial* p1 = CreatePolynomial(intField, 1);
    int c1_1 = 1, c1_0 = 2;
    SetCoeff(p1, 1, &c1_1);
    SetCoeff(p1, 0, &c1_0);
    printf("P1: "); PrintPolynomial(p1);

    // Создаем P2(x) = 1*x - 2
    Polynomial* p2 = CreatePolynomial(intField, 1);
    int c2_1 = 1, c2_0 = -2;
    SetCoeff(p2, 1, &c2_1);
    SetCoeff(p2, 0, &c2_0);
    printf("P2: "); PrintPolynomial(p2);

    // 1. Сложение (P1 + P2) = 2x
    Polynomial* pSum = CreatePolynomial(intField, 1);
    AddPolynomial(p1, p2, pSum);
    printf("P1 + P2: "); PrintPolynomial(pSum);

    // 2. Умножение на скаляр (P1 * 3) = 3x + 6
    int scalar = 3;
    ScalarMult(p1, &scalar);
    printf("P1 * 3:  "); PrintPolynomial(p1);

    // 3. Умножение многочленов (x+2)*(x-2) = x^2 - 4
    // Восстановим P1 в x + 2
    int r1 = 1, r0 = 2; SetCoeff(p1, 1, &r1); SetCoeff(p1, 0, &r0);
    Polynomial* pMul = CreatePolynomial(intField, 2);
    PolynomialMult(p1, p2, pMul);
    printf("P1 * P2: "); PrintPolynomial(pMul);

    // 4. Значение в точке (x^2 - 4) при x = 3 -> 9 - 4 = 5
    int dot = 3, res = 0;
    EvaluatePolynomial(pMul, &dot, &res);
    printf("Значение P1*P2 в точке x=3: %d\n\n", res);

    FreePolynomial(p1); FreePolynomial(p2); FreePolynomial(pSum); FreePolynomial(pMul);
}

void test_complex() {
    printf("=== ТЕСТИРОВАНИЕ ТИПА COMPLEX ===\n");
    FieldInfo* cField = GetComplexFieldInfo();

    // P1(x) = (1+1i)x + (2+0i)
    Polynomial* p1 = CreatePolynomial(cField, 1);
    Complex c1_1 = {1.0, 1.0}, c1_0 = {2.0, 0.0};
    SetCoeff(p1, 1, &c1_1);
    SetCoeff(p1, 0, &c1_0);
    printf("P1: "); PrintPolynomial(p1);

    // P2(x) = (1-1i)x + (0+1i)
    Polynomial* p2 = CreatePolynomial(cField, 1);
    Complex c2_1 = {1.0, -1.0}, c2_0 = {0.0, 1.0};
    SetCoeff(p2, 1, &c2_1);
    SetCoeff(p2, 0, &c2_0);
    printf("P2: "); PrintPolynomial(p2);

    // 1. Сложение: (2+0i)x + (2+1i)
    Polynomial* pSum = CreatePolynomial(cField, 1);
    AddPolynomial(p1, p2, pSum);
    printf("P1 + P2: "); PrintPolynomial(pSum);

    // 2. Умножение на скаляр: P1 * (2+0i) = (2+2i)x + (4+0i)
    Complex scalar = {2.0, 0.0};
    ScalarMult(p1, &scalar);
    printf("P1 * 2:  "); PrintPolynomial(p1);

    // 3. Умножение многочленов (восстановим P1)
    SetCoeff(p1, 1, &c1_1); SetCoeff(p1, 0, &c1_0);
    Polynomial* pMul = CreatePolynomial(cField, 2);
    PolynomialMult(p1, p2, pMul);
    printf("P1 * P2: "); PrintPolynomial(pMul);

    // 4. Значение в точке при x = (1+0i)
    Complex dot = {1.0, 0.0}, res = {0, 0};
    EvaluatePolynomial(pMul, &dot, &res);
    printf("Значение P1*P2 в точке x=1: (%.2f + %.2fi)\n\n", res.re, res.im);

    FreePolynomial(p1); FreePolynomial(p2); FreePolynomial(pSum); FreePolynomial(pMul);
}

int main() {
    test_int();
    test_complex();
    return 0;
}