#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "polynomial.h"
#include "tools.h"



void PrintListOfPolynomials(Polynomial* arr[], int count_polys)
{
    for (int number = 0; number < count_polys; number++)
    {
        printf("%d.  ", number + 1);
        PrintPolynomial(arr[number]);
        printf("\n");
    }
}