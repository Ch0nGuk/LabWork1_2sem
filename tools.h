#ifndef TOOLS_H
#define TOOLS_H


typedef enum 
{
    INT_TYPE,
    DOUBLE_TYPE
} NumType;

void PrintListOfPolynomials(Polynomial* arr[], int count_polys);

int read_num(void* str, NumType type);

int is_complex(double* re, double* im);


#endif // TOLLS_H