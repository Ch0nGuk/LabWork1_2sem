#ifndef TESTS_H
#define TESTS_H

void test_int_create();
void test_int_evaluate();
void test_int_derivative();

void test_complex_create();
void test_complex_evaluate();

void test_error_mismatched_types();
void test_error_invalid_degree();
void test_error_index_oob();
void test_error_small_buffer_for_mult();
void test_error_null_safety();

#endif // TESTS_H
