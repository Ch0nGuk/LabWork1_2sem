#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"
#include "field_info.h"
#include "print_list_polynomials.h"

void set_coef_in_menu(Polynomial *polys[], int *poly_id)
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
    int coeff_number;

    printf("There are %d coefficients of the polynomial\nWhich coefficient (0 - %d) do you want to select?\nChoice:  ", (int)poly->degree + 1, (int)poly->degree);

    if (!int_field->read(&coeff_number))
    {
        printf("ERROR! Invalid input\n");
        return;
    }
    printf("\n");

    if (coeff_number > (int)poly->degree || coeff_number < 0)
    {
        printf("ERROR! Wrong coefficient\n");
        return;
    }

    if (poly->polynomial_type == int_field)
    {
        printf("Polynomial's type is integer\nWrite coefficient value:  ");
        int data;

        if (!int_field->read(&data)) 
        {
            printf("ERROR! Wrong input\n");
            return;
        }
        printf("\n");

        set_coeff(poly, coeff_number, &data);
        printf("Succesfull set coefficient!\n");
    }

    if (poly->polynomial_type == complex_field)
    {
        Complex data;
        printf("Polynomial's type is complex\nWrite coefficient value (real and image part in different string):  ");

        if(!complex_field->read(&data))
        {
            printf("ERROR! Invalid input\n");
            return;
        }
        printf("\n");

        set_coeff(poly, coeff_number, &data);

        printf("Succesfull set coefficient!\n");
    }
}