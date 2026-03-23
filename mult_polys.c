#include <stdio.h>
#include <stdlib.h>
#include "field_info.h"
#include "polynomial.h"
#include "print_list_polynomials.h"

void mult_polynomial_in_menu(Polynomial *polys[], int *poly_id)
{
    if (*poly_id <= 1)
    {
        printf("Too few polynomials\n");
        return;
    }

    FieldInfo* int_field = get_int_field_info();
    FieldInfo* complex_field = get_complex_field_info();

    int first_num, second_num;

    printf("There are %d polynomials\n", *poly_id);
    print_list_of_polynomials(polys, *poly_id);
    printf("Write first polynomial:   ");

    if (!int_field->read(&first_num))
    {
        printf("ERROR! Invalid input\n");
        return;
    }

    if (first_num > *poly_id || first_num <= 0)
    {
        printf("ERROR! Wrong number\n");
        return;
    }

    printf("\n");
    printf("Write second polynomial:   ");

    if (!int_field->read(&second_num))
    {
        printf("ERROR! Invalid input\n");
        return;
    }

    if (second_num > *poly_id || second_num <= 0)
    {
        printf("ERROR! Wrong number\n");
        return;
    }

    printf("\n");

    if (polys[first_num - 1]->polynomial_type != polys[second_num - 1]->polynomial_type)
    {
        printf("ERROR! Different types of polynomials\n");
        return;
    }

    Polynomial* poly1 = polys[first_num - 1];
    Polynomial* poly2 = polys[second_num - 1];

    Polynomial* mult_pol = create_polynomial(poly1->polynomial_type, poly1->degree + poly2->degree);

    mult_polynomial(poly1, poly2, mult_pol);

    polys[*poly_id++] = mult_pol;

    printf("Succesfull multiple polynomials!\n");
    printf("New polynomials:\n");

    print_polynomial(poly1);

    printf("  *  ");

    print_polynomial(poly2);

    printf("  =  ");

    print_polynomial(mult_pol);

    printf("\n");
}