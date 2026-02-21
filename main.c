#include "polynomial.h"
#include "field_info.h"
#include <stdio.h>

int main() {
    // 1. Берем описание типа (например, INT)
    // FieldInfo* intField = GetIntFieldInfo();

    // // 2. Создаем многочлен степени 2 (ax^2 + bx + c)
    // Polynomial* p = CreatePolynomial(intField, 2);

    // // 3. Задаем коэффициенты: 5x^2 + 0x + 3
    // int c2 = 5, c1 = 0, c0 = 3;
    // SetCoeff(p, 2, &c2);
    // SetCoeff(p, 1, &c1);
    // SetCoeff(p, 0, &c0);

    // // 4. Печатаем, что получилось
    // PrintPolynomial(p);

    // // 5. Считаем значение в точке x = 2
    // int x = 2, result = 0;
    // EvaluatePolynomial(p, &x, &result);
    // printf("Result at x=2: %d\n", result); // Ожидаем 5*(2^2) + 3 = 23

    // FreePolynomial(p);

    FieldInfo* complexField = GetComplexFieldInfo();
    Polynomial* p = CreatePolynomial(complexField, 1);
    Complex co1 = {1.0, 3.0}, co2 = {2., 4.};
    SetCoeff(p, 1, &co1);
    SetCoeff(p, 0, &co2);
    PrintPolynomial(p);
    printf("\n");
    FreePolynomial(p);
    return 0;
}