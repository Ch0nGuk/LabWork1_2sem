#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polynomial.h"
#include "field_info.h"
#include "print_list_polynomials.h"
#include "tests.h"
#include "create_polynomial.h"
#include "set_coef.h"
#include "evaluate_polynomial.h"
#include "add_polynomials.h"
#include "mult_by_scalar.h"
#include "mult_polys.h"
#include "derivative.h"

void menu()
{   
    FieldInfo* int_field = get_int_field_info();
    FieldInfo* complex_field = get_complex_field_info();

    Polynomial* polys[10];
    int poly_id = 0;

    printf("\n========READ IT========\n\n");
    printf("Polynomial has the form: An*X^n + A(n-1)*X^(n-1) + ... + A1*X + A0\n");
    printf("The degree of polynomial is the number  N\n");
    printf("The count of term (Ai*X^i) is  (N + 1)\n\n");
    printf("\nWhen we write Nth coefficent, we write An\n");
    printf("So, 3x^2 + 45x + -3\n");
    printf("    |       |     |\n");
    printf("   2th coef |     0th coef\n");
    printf("            |\n");
    printf("           1th coef \n\n");

    while (1)
    {
        printf("\n\n-------- MENU of Polynomial --------\n\n");
        printf("Select the command:\n\n");
        printf("1.  Create polynomial\n");
        printf("2.  Set coefficient\n");
        printf("3.  Print polynomial\n");
        printf("4.  Find the value of the polynomial at a point\n");
        printf("5.  Add polynomials\n");
        printf("6.  Multiply polynomial by scalar\n");
        printf("7.  Multiply polynomials\n");
        printf("8.  Derivative polynomial\n");
        printf("9.  Run tests\n");
        printf("0.  Exit\n");
        printf("\nChoice:  ");

        int menu_choice;
        if (!int_field->read(&menu_choice))
        {
            printf("\nERROR! Invalid input\n");
            continue;
        }

        if (menu_choice == 0) break;

        switch (menu_choice)
        {
        case 1: // Create polynomial
        {
            create_poly_in_menu(polys, &poly_id);
            break;
        }

        case 2: // Set coefficient
        {
            set_coef_in_menu(polys, &poly_id);
            break;
        }

        case 3: // Print polynomial
        {
            if (poly_id == 0) { printf("ERROR!\n"); continue; }
            print_list_of_polynomials(polys, poly_id);
            break;
        }

        case 4: // Evaluate
        {
            evaluate_polynomial_in_menu(polys, &poly_id);
            break;
        }

        case 5: // Add
        {
            add_polynomials_in_menu(polys, &poly_id);
            break;
        }

        case 6: // Mult scalar
        {
            mult_scalar_in_menu(polys, &poly_id);
            break;
        }

        case 7: // Mult polys
        {
            mult_polynomial_in_menu(polys, &poly_id);
            break;
        }

        case 8: // Derivative
        {
            derivative_in_menu(polys, &poly_id);
            break;
        }

        // case 9: // Tests
        // {
        //     test_complex();
        //     test_int();
        //     break;
        // }

        default:
            printf("\nERROR! Invalid command.\n");
            continue;
        }
    }
}