#include "print_list_polynomials.h"
#include <stdio.h>

void print_list_of_polynomials(Polynomial* arr[], int count_polys)
{
    for (int number = 0; number < count_polys; number++)
    {
        printf("%d.  ", number + 1);
        print_polynomial(arr[number]);
        printf("\n");
    }
}