#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polynomial.h"
#include "field_info.h"

Polynomial* create_polynomial(FieldInfo* f_info, int degree) {
    if (degree < 0) return NULL;

    Polynomial* poly = (Polynomial*)malloc(sizeof(Polynomial));
    if (poly == NULL) return NULL;

    poly->polynomial_type = f_info;
    poly->degree = degree;
    poly->coefficients = malloc(f_info->size * (degree + 1));

    if (poly->coefficients == NULL) {
        free(poly);
        return NULL;
    }

    memset(poly->coefficients, 0, f_info->size * (degree + 1));
    return poly;
}

void free_polynomial(Polynomial* poly) {
    if (poly == NULL) return;
    if (poly->coefficients != NULL) {
        free(poly->coefficients);
    }
    free(poly);
}

static void* get_coeff_ptr(Polynomial* poly, int index) {
    if (poly == NULL || index < 0 || index > poly->degree) {
        return NULL;
    }
    return (char*)poly->coefficients + (index * poly->polynomial_type->size);
}

void set_coeff(Polynomial* poly, int index, void* src) {
    void* target = get_coeff_ptr(poly, index);
    if (target != NULL && src != NULL) {
        memcpy(target, src, poly->polynomial_type->size);
    }
}

void print_polynomial(Polynomial* poly) {
    if (poly == NULL) return;

    for (int deg = poly->degree; deg >= 0; deg--) {
        void* coeff_addr = get_coeff_ptr(poly, deg);
        poly->polynomial_type->print(coeff_addr);

        if (deg > 1) {
            printf("*x^%d + ", deg);
        } else if (deg == 1) {
            printf("*x + ");
        }
    }
}

void evaluate_polynomial(Polynomial* poly, void* dot, void* result) {
    if (poly == NULL || dot == NULL || result == NULL) return;

    void* senior_coeff = get_coeff_ptr(poly, poly->degree);
    memcpy(result, senior_coeff, poly->polynomial_type->size);

    for (int deg = poly->degree - 1; deg >= 0; deg--) {
        poly->polynomial_type->mult(result, dot, result);
        void* current_coeff = get_coeff_ptr(poly, deg);
        poly->polynomial_type->add(result, current_coeff, result);
    }
}

void add_polynomial(Polynomial* poly1, Polynomial* poly2, Polynomial* result_poly) {
    if (poly1->polynomial_type != poly2->polynomial_type || 
        poly1->polynomial_type != result_poly->polynomial_type) return;

    void* temp_sum = malloc(poly1->polynomial_type->size);
    if (temp_sum == NULL) return;

    int max_degree = poly1->degree >= poly2->degree ? poly1->degree : poly2->degree;

    for (int deg = max_degree; deg >= 0; deg--) {
        void* coef1 = get_coeff_ptr(poly1, deg);
        void* coef2 = get_coeff_ptr(poly2, deg);

        if (coef1 != NULL && coef2 != NULL) {
            poly1->polynomial_type->add(coef1, coef2, temp_sum);
        } else if (coef2 == NULL) {
            memcpy(temp_sum, coef1, poly1->polynomial_type->size);
        } else if (coef1 == NULL) {
            memcpy(temp_sum, coef2, poly2->polynomial_type->size);
        }

        set_coeff(result_poly, deg, temp_sum);
    }
    free(temp_sum);
}

void mult_scalar(Polynomial* poly, void* scalar) {
    if (poly == NULL || scalar == NULL) return;

    for (int deg = poly->degree; deg >= 0; deg--) {
        void* coef = get_coeff_ptr(poly, deg);
        poly->polynomial_type->mult(coef, scalar, coef);
    }
}

void mult_polynomial(Polynomial* poly1, Polynomial* poly2, Polynomial* result_poly) {
    if (poly1->polynomial_type != poly2->polynomial_type || 
        poly1->polynomial_type != result_poly->polynomial_type) return;

    if (result_poly->degree < poly1->degree + poly2->degree) return;

    void* new_coef = malloc(result_poly->polynomial_type->size);
    if (new_coef == NULL) return;

    memset(result_poly->coefficients, 0, result_poly->polynomial_type->size * (result_poly->degree + 1));

    for (int d1 = poly1->degree; d1 >= 0; d1--) {
        for (int d2 = poly2->degree; d2 >= 0; d2--) {   
            int res_deg = d1 + d2;
            void* c1 = get_coeff_ptr(poly1, d1);
            void* c2 = get_coeff_ptr(poly2, d2);

            poly1->polynomial_type->mult(c1, c2, new_coef);
            result_poly->polynomial_type->add(new_coef, get_coeff_ptr(result_poly, res_deg), new_coef);
            set_coeff(result_poly, res_deg, new_coef);
        }
    }
    free(new_coef);
}

Polynomial* derivative_of_polynomial(Polynomial* poly) {
    if (poly == NULL) return NULL;
    
    if (poly->degree == 0) {
        return create_polynomial(poly->polynomial_type, 0);
    }

    Polynomial* diff_poly = create_polynomial(poly->polynomial_type, poly->degree - 1);
    void* diff_coeff = malloc(poly->polynomial_type->size);
    if (diff_coeff == NULL) return NULL;

    for (int deg = poly->degree; deg > 0; deg--) {
        void* tmp_coeff = get_coeff_ptr(poly, deg);
        poly->polynomial_type->derivop(tmp_coeff, deg, diff_coeff);
        set_coeff(diff_poly, deg - 1, diff_coeff);
    }

    free(diff_coeff);
    return diff_poly;
}