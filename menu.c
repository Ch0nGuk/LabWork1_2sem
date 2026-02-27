#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polynomial.h"
#include "field_info.h"
#include "tools.h"
#include "tests.h"



void menu()
{   
    FieldInfo* IntField = GetIntFieldInfo();
    FieldInfo* ComplexField = GetComplexFieldInfo();

    Polynomial* polys[10];
    int poly_id = 0;

    printf("\n========README========\n\n");
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
        printf("4.  Find the value at the point\n");
        printf("5.  Add 2 polynomials\n");
        printf("6.  Multiply polynomial by a scalar\n");
        printf("7.  Multiply 2 polynomials\n");
        printf("8.  Derivative a polynomial\n");
        printf("9.  Run tests\n");
        printf("0.  Exit\n");
        printf("Choice: ");

        int menu_choice;

        if ( !read_num(&menu_choice, INT_TYPE) ) 
        {
            printf("\nERROR! Invalid command.\n");
            continue;
        }
        printf("\n");

        switch (menu_choice)
        {

        case 0:

            for (int poly = 0; poly < poly_id; poly++)
            {
                FreePolynomial(polys[poly]);
            }

            return;

        case 1: // Create polynomial
        {

            int coeff_type;
            int degree;

            printf("Write degree of polynomial (it must be positive int):    ");

            if (!read_num(&degree, INT_TYPE) || degree < 0)
            {
                printf("ERROR! Invalid degree\n");
                continue;
            }
            printf("\n");

            printf("1.  With integer coefficients\n2.  With complex coefficients\nChoice:  ");

            if (!read_num(&coeff_type, INT_TYPE))
            {
                printf("ERROR! Invalid input\n");
                continue;
            }
            printf("\n");

            switch (coeff_type) 
            {
            case 1: // Int polynomial
                polys[poly_id++] = CreatePolynomial(IntField, degree);

                for (int index = degree; index >= 0; index--)
                {   
                    int coeff;
                    printf("Write %dth coefficient:  ", index);

                    if (!read_num(&coeff, INT_TYPE))
                    {
                        printf("ERROR! Invalid input. Try again!\n");
                        index++;
                        continue;
                    }

                    SetCoeff(polys[poly_id - 1], index, &coeff);

                    printf("\n");
                }

                printf("Succesfull create integer polynomial!\n");
                printf("New polynomials:\n");

                PrintPolynomial(polys[poly_id - 1]);
                printf("\n");
                break;
            
            case 2: // Complex polynomial
                polys[poly_id++] = CreatePolynomial(ComplexField, degree);

                for (int index = degree; index >= 0; index--)
                {
                    double re, im;
                    printf("Write real part of %dth index:  ", index);

                    if (!read_num(&re, DOUBLE_TYPE))
                    {
                        printf("ERROR! Invalid input. Try again!\n");
                        index++;
                        continue;
                    }

                    printf("Write image part of %dth index:  ", index);

                    if (!read_num(&im, DOUBLE_TYPE))
                    {
                        printf("ERROR! Invalid input. Try again!\n");
                        index++;
                        continue;
                    }

                    Complex coeff = {re, im};

                    SetCoeff(polys[poly_id - 1], index, &coeff);

                    printf("\n");
                }

                printf("Succesfull create complex polynomial!\n");
                printf("New polynomials:\n");

                PrintPolynomial(polys[poly_id - 1]);
                printf("\n");
                break;

            default:
                printf("Error! Invalid input\n");
                continue;
                break;
            }

            break;
        
        }
        
        case 2: // Set coefficient
        {
            if (poly_id == 0)
            {
                printf("ERROR! Not a polynomial has been created\n");
                continue;
            }

            printf("There are %d polynomials now\n", poly_id);
            PrintListOfPolynomials(polys, poly_id);
            printf("Which polynomials do you want to select?\nChoice:  ");

            int poly_number;
            
            if (!read_num(&poly_number, INT_TYPE))
            {
                printf("ERROR! Invalid input\n");
                continue;
            }
            printf("\n");

            if (poly_number > poly_id || poly_number <= 0)
            {
                printf("ERROR! Wrong number\n");
                continue;
            }

            Polynomial* poly = polys[poly_number - 1];
            int coeff_number;

            printf("There are %d coefficients of the polynomial\nWhich coefficient (0 - %d) do you want to select?\nChoice:  ", (int)poly->count, (int)poly->count - 1);

            if (!read_num(&coeff_number, INT_TYPE))
            {
                printf("ERROR! Invalid input\n");
                continue;
            }
            printf("\n");

            if (coeff_number > (int)poly->count - 1 || coeff_number <= 0)
            {
                printf("ERROR! Wrong coefficient\n");
                continue;
            }

            if (poly->polynomial_type == IntField)
            {
                printf("Polynomial's type is integer\nWrite coefficient value:  ");
                int data;

                if (!read_num(&data, INT_TYPE)) 
                {
                    printf("ERROR! Wrong input\n");
                    continue;
                }
                printf("\n");

                SetCoeff(poly, coeff_number, &data);
                printf("Succesfull set coefficient!\n");
            }

            if (poly->polynomial_type == ComplexField)
            {
                double re, im;
                printf("Polynomial's type is complex\nWrite real coefficient value:  ");

                if (!read_num(&re, DOUBLE_TYPE)) 
                {
                    printf("ERROR! Invalid input\n");
                    continue;
                }
                printf("\n");

                printf("Write image coefficient value:  ");

                if(!read_num(&im, DOUBLE_TYPE))
                {
                    printf("ERROR! Invalid input\n");
                    continue;
                }
                printf("\n");

                Complex data = {re, im};

                SetCoeff(poly, coeff_number, &data);

                printf("Succesfull set coefficient!\n");
            }

            break;
        }

        case 3: // Print polynomial
        {
        
            if (poly_id == 0)
            {
                printf("ERROR! Not a polynomial has been created\n");
                continue;
            }

            printf("There are %d polynomials now\n", poly_id);
            PrintListOfPolynomials(polys, poly_id);
            printf("Which polynomials do you want to select?\nChoice:  ");

            int poly_number;
            
            if (!read_num(&poly_number, INT_TYPE))
            {
                printf("ERROR! Invalid input\n");
                continue;
            }
            printf("\n");

            if (poly_number > poly_id || poly_number <= 0)
            {
                printf("ERROR! Wrong number\n");
                continue;
            }
            
            printf("Polynomial %d:\n", poly_number);
            PrintPolynomial(polys[poly_number - 1]);
            printf("\n");

            break;

        }

        case 4: // Find value at point
        {

            if (poly_id == 0)
            {
                printf("ERROR! Not a polynomial has been created\n");
                continue;
            }

            printf("There are %d polynomials now\n", poly_id);
            PrintListOfPolynomials(polys, poly_id);
            printf("Which polynomials do you want to select?\nChoice:  ");
            int poly_number;
            
            if (!read_num(&poly_number, INT_TYPE))
            {
                printf("ERROR! Invalid input\n");
                continue;
            }
            printf("\n");

            if (poly_number > poly_id || poly_number <= 0)
            {
                printf("ERROR! Wrong number\n");
                continue;
            }

            Polynomial* poly = polys[poly_number - 1];

            if (poly->polynomial_type == IntField)
            {
                printf("This polynomial has integer type\nWrite integer dot, where find value:  ");
                int dot;

                if (!read_num(&dot, INT_TYPE))
                {
                    printf("ERROR! Wrong input\n");
                    continue;
                }

                printf("\n");

                int result;

                EvaluatePolynomial(poly, &dot, &result);
                printf("Value of polynomial at the dot  %d  is  %d\n", dot, result);
            }

            if (poly->polynomial_type == ComplexField)
            {
                double re, im;

                printf("This polynomial has complex type\nWrite real part of dot, where find value:  ");
                if(!read_num(&re, DOUBLE_TYPE))
                {
                    printf("ERROR! Invalid input\n");
                    continue;
                }

                printf("\n");
                printf("Write image part of dot, where find value:  ");
                if(!read_num(&im, DOUBLE_TYPE))
                {
                    printf("ERROR! Invalid input\n");
                    continue;
                }

                Complex dot = {re, im};

                Complex* result = malloc(sizeof(Complex));

                EvaluatePolynomial(poly, &dot, result);

                printf("Value of polynomial at the dot  ");
                ComplexField->print(&dot);
                printf("  is  ");
                ComplexField->print(result);
                printf("\n");
                free(result);

            }

            break;

        }

        case 5: // Add 2 polynomials
        {
            if (poly_id <= 1)
            {
                printf("Too few polynomials\n");
                continue;
            }

            int first_num, second_num;

            printf("There are %d polynomials\n", poly_id);
            PrintListOfPolynomials(polys, poly_id);
            printf("Write first polynomial:   ");

            if (!read_num(&first_num, INT_TYPE))
            {
                printf("ERROR! Invalid input\n");
                continue;
            }

            if (first_num > poly_id || first_num <= 0)
            {
                printf("ERROR! Wrong number\n");
                continue;
            }

            printf("\n");
            printf("Write second polynomial:   ");

            if (!read_num(&second_num, INT_TYPE))
            {
                printf("ERROR! Invalid input\n");
                continue;
            }

            if (second_num > poly_id || second_num <= 0)
            {
                printf("ERROR! Wrong number\n");
                continue;
            }

            printf("\n");

            if (polys[first_num - 1]->polynomial_type != polys[second_num - 1]->polynomial_type)
            {
                printf("ERROR! Different types of polynomials\n");
                continue;
            }

            Polynomial* poly1 = polys[first_num - 1];
            Polynomial* poly2 = polys[second_num - 1];

            Polynomial* add_pol = CreatePolynomial(poly1->polynomial_type, poly1->count >= poly2->count ? (int)poly1->count - 1 : (int)poly2->count - 1);

            AddPolynomial(poly1, poly2, add_pol);

            polys[poly_id++] = add_pol;

            printf("Succesfull add polynomials!\n");
            printf("New polynomials:\n");

            PrintPolynomial(poly1);

            printf("  +  ");

            PrintPolynomial(poly2);

            printf("  =  ");

            PrintPolynomial(add_pol);

            printf("\n");

            break;
        }

        case 6: // Mulitple scalar
        {

            if (poly_id == 0)
            {
                printf("ERROR! Not a polynomial has been created\n");
                continue;
            }

            printf("There are %d polynomials now\n", poly_id);
            PrintListOfPolynomials(polys, poly_id);
            printf("Which polynomials do you want to select?\nChoice:  ");

            int poly_number;
            
            if (!read_num(&poly_number, INT_TYPE))
            {
                printf("ERROR! Invalid input\n");
                continue;
            }
            printf("\n");

            if (poly_number > poly_id || poly_number < 0)
            {
                printf("ERROR! Wrong number\n");
                continue;
            }

            Polynomial* poly = polys[poly_number - 1];

            if (poly->polynomial_type == IntField)
            {
                printf("This polynomial has integer type\nWrite integer scalar:  ");
                int dot;

                if (!read_num(&dot, INT_TYPE))
                {
                    printf("ERROR! Wrong input\n");
                    continue;
                }

                printf("\n");

                int result;

                ScalarMult(poly, &dot);
                printf("Succesfull multiply polynomial at scalar:  ");
                PrintPolynomial(poly);
                printf("\n");
            }

            if (poly->polynomial_type == ComplexField)
            {
                double re, im;

                printf("This polynomial has complex type\nWrite real part of scalar:  ");
                if(!read_num(&re, DOUBLE_TYPE))
                {
                    printf("ERROR! Invalid input\n");
                    continue;
                }

                printf("\n");
                printf("Write image part of scalar:  ");
                if(!read_num(&im, DOUBLE_TYPE))
                {
                    printf("ERROR! Invalid input\n");
                    continue;
                }

                Complex dot = {re, im};

                ScalarMult(poly, &dot);

                printf("Succesfull multiply polynomial at scalar:  ");
                PrintPolynomial(poly);
                printf("\n");
            }

            break;

        }

        case 7: // Multiple polynomials
        {

            if (poly_id <= 1)
            {
                printf("Too few polynomials\n");
                continue;
            }

            int first_num, second_num;

            printf("There are %d polynomials\n", poly_id);
            PrintListOfPolynomials(polys, poly_id);
            printf("Write first polynomial:   ");

            if (!read_num(&first_num, INT_TYPE))
            {
                printf("ERROR! Invalid input\n");
                continue;
            }

            if (first_num > poly_id || first_num <= 0)
            {
                printf("ERROR! Wrong number\n");
                continue;
            }

            printf("\n");
            printf("Write second polynomial:   ");

            if (!read_num(&second_num, INT_TYPE))
            {
                printf("ERROR! Invalid input\n");
                continue;
            }

            if (second_num > poly_id || second_num <= 0)
            {
                printf("ERROR! Wrong number\n");
                continue;
            }

            printf("\n");

            if (polys[first_num - 1]->polynomial_type != polys[second_num - 1]->polynomial_type)
            {
                printf("ERROR! Different types of polynomials\n");
                continue;
            }

            Polynomial* poly1 = polys[first_num - 1];
            Polynomial* poly2 = polys[second_num - 1];

            Polynomial* mult_pol = CreatePolynomial(poly1->polynomial_type, poly1->count >= poly2->count ? (int)poly1->count - 1 : (int)poly2->count - 1);

            PolynomialMult(poly1, poly2, mult_pol);

            polys[poly_id++] = mult_pol;

            printf("Succesfull multiple polynomials!\n");
            printf("New polynomials:\n");

            PrintPolynomial(poly1);

            printf("  *  ");

            PrintPolynomial(poly2);

            printf("  =  ");

            PrintPolynomial(mult_pol);

            printf("\n");

            break;

        }

        case 8: // Derivative polynomial
        {

            if (poly_id == 0)
            {
                printf("ERROR! Not a polynomial has been created\n");
                continue;
            }

            printf("There are %d polynomials now\n", poly_id);
            PrintListOfPolynomials(polys, poly_id);
            printf("Which polynomials do you want to select?\nChoice:  ");
            int poly_number;
            
            if (!read_num(&poly_number, INT_TYPE))
            {
                printf("ERROR! Invalid input\n");
                continue;
            }
            printf("\n");

            if (poly_number > poly_id || poly_number <= 0)
            {
                printf("ERROR! Wrong number\n");
                continue;
            }

            Polynomial* poly = polys[poly_number - 1];

            Polynomial* diff_poly = DerivativeOfPolynomial(poly);

            polys[poly_id++] = diff_poly;

            printf("Succesfull took the derivative of the polynomial:  ");
            PrintPolynomial(diff_poly);
            printf("\n");

            break;
        }


        case 9:
        {

            test_complex();
            test_int();

            break;

        }
        

        default:
            printf("\nERROR! Invalid command.\n");
            continue;
            break;
        }



    }

}