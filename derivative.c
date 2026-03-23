#include <stdio.h>
#include <stdlib.h>
#include "field_info.h"
#include "polynomial.h"
#include "print_list_polynomials.h"

void derivative_in_menu(Polynomial *polys[], int *poly_id)
{
    if (*poly_id == 0)
    {
        printf("ERROR! Not a polynomial has been created\n");
        return;
    }

    FieldInfo* int_field = get_int_field_info();
    FieldInfo* complex_field = get_complex_field_info();

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

    Polynomial* diff_poly = derivative_of_polynomial(poly);

    polys[(*poly_id)++] = diff_poly;

    printf("Succesfull took the derivative of the polynomial:  ");
    print_polynomial(diff_poly);
    printf("\n");
}