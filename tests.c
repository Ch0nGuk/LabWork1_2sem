#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "polynomial.h"
#include "field_info.h"
#include "tests.h"

#define GET_COEFF(p, i) ((char*)(p)->coefficients + (i) * (p)->polynomial_type->size)

void test_int_create() {
    printf("\n--- RUNNING INT CREATE TEST ---\n");
    FieldInfo* f = get_int_field_info();

    printf("Creating P1 = 2x + 3... ");
    Polynomial* p1 = create_polynomial(f, 1);
    int c0 = 3, c1 = 2;
    set_coeff(p1, 0, &c0);
    set_coeff(p1, 1, &c1);
    printf("OK\n");

    free_polynomial(p1);
    printf("--- INT CREATE TEST FINISHED ---\n");
}

void test_int_evaluate() {
    printf("\n--- RUNNING INT EVALUATE TEST ---\n");
    FieldInfo* f = get_int_field_info();

    printf("Creating P1 = 2x + 3... ");
    Polynomial* p1 = create_polynomial(f, 1);
    int c0 = 3, c1 = 2;
    set_coeff(p1, 0, &c0);
    set_coeff(p1, 1, &c1);
    printf("OK\n");

    printf("Evaluating P1 at x=2... ");
    int res, x = 2;
    evaluate_polynomial(p1, &x, &res);
    assert(res == 7);
    printf("Result: %d (OK)\n", res);

    free_polynomial(p1);
    printf("--- INT EVALUATE TEST FINISHED ---\n");
}

void test_int_derivative() {
    printf("\n--- RUNNING INT DERIVATIVE TEST ---\n");
    FieldInfo* f = get_int_field_info();

    printf("Creating P1 = 2x + 3... ");
    Polynomial* p1 = create_polynomial(f, 1);
    int c0 = 3, c1 = 2;
    set_coeff(p1, 0, &c0);
    set_coeff(p1, 1, &c1);
    printf("OK\n");

    printf("Calculating derivative... ");
    Polynomial* pd = derivative_of_polynomial(p1);
    assert(pd->degree == 0);
    assert(*(int*)GET_COEFF(pd, 0) == 2);
    printf("Result degree 0, coeff 2 (OK)\n");

    free_polynomial(p1);
    free_polynomial(pd);
    printf("--- INT DERIVATIVE TEST FINISHED ---\n");
}

void test_complex_create() {
    printf("\n--- RUNNING COMPLEX CREATE TEST ---\n");
    FieldInfo* f = get_complex_field_info();

    printf("Creating P = (1+1i)x + 2... ");
    Polynomial* p = create_polynomial(f, 1);
    Complex c0 = {2.0, 0.0}, c1 = {1.0, 1.0};
    set_coeff(p, 0, &c0);
    set_coeff(p, 1, &c1);
    printf("OK\n");

    free_polynomial(p);
    printf("--- COMPLEX CREATE TEST FINISHED ---\n");
}

void test_complex_evaluate() {
    printf("\n--- RUNNING COMPLEX EVALUATE TEST ---\n");
    FieldInfo* f = get_complex_field_info();

    printf("Creating P = (1+1i)x + 2... ");
    Polynomial* p = create_polynomial(f, 1);
    Complex c0 = {2.0, 0.0}, c1 = {1.0, 1.0};
    set_coeff(p, 0, &c0);
    set_coeff(p, 1, &c1);
    printf("OK\n");

    printf("Evaluating P at x=(2+0i)... ");
    Complex res, x = {2.0, 0.0};
    evaluate_polynomial(p, &x, &res);
    assert(res.re == 4.0 && res.im == 2.0);
    printf("Result: %.1f + %.1fi (OK)\n", res.re, res.im);

    free_polynomial(p);
    printf("--- COMPLEX EVALUATE TEST FINISHED ---\n");
}

void test_error_mismatched_types() {
    printf("\n--- RUNNING MISMATCHED TYPES TEST ---\n");
    FieldInfo* fi = get_int_field_info();
    FieldInfo* fc = get_complex_field_info();

    printf("1. Testing mismatched types (int + complex): ");
    Polynomial* pi = create_polynomial(fi, 1);
    Polynomial* pc = create_polynomial(fc, 1);
    Polynomial* pr = create_polynomial(fi, 1);
    int guard = 999;
    set_coeff(pr, 0, &guard);
    add_polynomial(pi, pc, pr);
    assert(*(int*)GET_COEFF(pr, 0) == 999);
    printf("BLOCKED OK\n");

    free_polynomial(pi);
    free_polynomial(pc);
    free_polynomial(pr);
    printf("--- MISMATCHED TYPES TEST FINISHED ---\n");
}

void test_error_invalid_degree() {
    printf("\n--- RUNNING INVALID DEGREE TEST ---\n");
    FieldInfo* fi = get_int_field_info();

    printf("2. Testing invalid degree (-1): ");
    assert(create_polynomial(fi, -1) == NULL);
    printf("RETURNED NULL OK\n");

    printf("--- INVALID DEGREE TEST FINISHED ---\n");
}

void test_error_index_oob() {
    printf("\n--- RUNNING INDEX OOB TEST ---\n");
    FieldInfo* fi = get_int_field_info();
    Polynomial* pi = create_polynomial(fi, 1);

    printf("3. Testing index OOB (index 10 for degree 1): ");
    int val = 50;
    set_coeff(pi, 10, &val);
    assert(*(int*)GET_COEFF(pi, 0) == 0);
    printf("WRITE BLOCKED OK\n");

    free_polynomial(pi);
    printf("--- INDEX OOB TEST FINISHED ---\n");
}

void test_error_small_buffer_for_mult() {
    printf("\n--- RUNNING SMALL BUFFER MULT TEST ---\n");
    FieldInfo* fi = get_int_field_info();
    Polynomial* pi = create_polynomial(fi, 1);

    printf("4. Testing small buffer for mult: ");
    Polynomial* ps = create_polynomial(fi, 0);
    mult_polynomial(pi, pi, ps);
    assert(ps->degree == 0);
    printf("MULT BLOCKED OK\n");

    free_polynomial(pi);
    free_polynomial(ps);
    printf("--- SMALL BUFFER MULT TEST FINISHED ---\n");
}

void test_error_null_safety() {
    printf("\n--- RUNNING NULL SAFETY TEST ---\n");

    printf("5. Testing NULL safety (free & evaluate): ");
    free_polynomial(NULL);
    evaluate_polynomial(NULL, NULL, NULL);
    printf("NO CRASH OK\n");

    printf("--- NULL SAFETY TEST FINISHED ---\n");
}
