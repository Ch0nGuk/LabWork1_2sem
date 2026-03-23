#include <stdio.h>
#include <stdlib.h>
#include "field_info.h"
#include "polynomial.h"
#include "print_list_polynomials.h"

void evaluate_polynomial_in_menu(Polynomial *polys[], int *poly_id)
{
    if (*poly_id == 0) { printf("ERROR!\n"); return; }

    FieldInfo* int_field = get_int_field_info();
    FieldInfo* complex_field = get_complex_field_info();

    if (*poly_id == 0)
    {
        printf("ERROR! Not a polynomial has been created\n");
        return;
    }

    printf("There are %d polynomials now\n", *poly_id);
    print_list_of_polynomials(polys, *poly_id);
    printf("Which polynomials do you want to select?\nChoice:  ");
    int poly_number;
    
    if (!int_field->read(&poly_number))
    {
        printf("ERROR! Invalid input\n");
        return;
    }
    printf("\n");

    if (poly_number > *poly_id || poly_number <= 0)
    {
        printf("ERROR! Wrong number\n");
        return;
    }

    Polynomial* poly = polys[poly_number - 1];

    if (poly->polynomial_type == int_field)
    {
        printf("This polynomial has integer type\nWrite integer dot, where find value:  ");
        int dot;

        if (!int_field->read(&dot))
        {
            printf("ERROR! Wrong input\n");
            return;
        }

        printf("\n");

        int result;

        evaluate_polynomial(poly, &dot, &result);
        printf("Value of polynomial at the dot  %d  is  %d\n", dot, result);
    }

    if (poly->polynomial_type == complex_field)
    {
        Complex dot;
        printf("Polynomial's type is complex\nWrite coefficient value (real and image part in different string):  ");

        if(!complex_field->read(&dot))
        {
            printf("ERROR! Invalid input\n");
            return;
        }
        printf("\n");

        Complex* result = malloc(sizeof(Complex));

        evaluate_polynomial(poly, &dot, result);

        printf("Value of polynomial at the dot  ");
        complex_field->print(&dot);
        printf("  is  ");
        complex_field->print(result);
        printf("\n");
        free(result);

    }

}