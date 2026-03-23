#include <stdio.h>
#include "field_info.h"
#include "polynomial.h"



void create_poly_in_menu(Polynomial *polys[], int *poly_id)
{

    if (*poly_id >= 10)
    {
        printf("ERROR! Max count of polynomials reached\n");
        return;
    }

    FieldInfo* int_field = get_int_field_info();
    FieldInfo* complex_field = get_complex_field_info();

    int coeff_type;
        int degree;

        printf("Write degree of polynomial (it must be positive int):    ");

        if (!int_field->read(&degree) || degree < 0)
        {
            printf("ERROR! Invalid degree\n");
        }
        printf("\n");

        printf("1.  With integer coefficients\n2.  With complex coefficients\nChoice:  ");

        if (!int_field->read(&coeff_type))
        {
            printf("ERROR! Invalid input\n");
            
        }
        printf("\n");

        switch (coeff_type) 
        {
        case 1: // Int polynomial
            polys[(*poly_id)++] = create_polynomial(int_field, degree);

            for (int index = degree; index >= 0; index--)
            {   
                int coeff;
                printf("Write %dth coefficient:  ", index);

                if (!int_field->read(&coeff))
                {
                    printf("ERROR! Invalid input. Try again!\n");
                    index++;
                    return;
                }

                set_coeff(polys[(*poly_id) - 1], index, &coeff);

                printf("\n");
            }

            printf("Succesfull create integer polynomial!\n");
            printf("New polynomials:\n");

            print_polynomial(polys[(*poly_id) - 1]);
            printf("\n");
            break;
        
        case 2: // Complex polynomial
            polys[(*poly_id)++] = create_polynomial(complex_field, degree);

            for (int index = degree; index >= 0; index--)
            {
                Complex coeff;
                printf("Write %dth index (real and image part in different string):  ", index);

                if (!complex_field->read(&coeff))
                {
                    printf("ERROR! Invalid input. Try again!\n");
                    index++;
                    return;
                }

                set_coeff(polys[(*poly_id) - 1], index, &coeff);

                printf("\n");
            }

            printf("Succesfull create complex polynomial!\n");
            printf("New polynomials:\n");

            print_polynomial(polys[(*poly_id) - 1]);
            printf("\n");
            break;

        default:
            printf("Error! Invalid input\n");
            
            
        }

        
        
        
}



