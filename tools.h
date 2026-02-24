#ifndef TOOLS_H
#define TOOLS_H


typedef enum 
{
    INT_TYPE,
    DOUBLE_TYPE
} NumType;


int read_num(void* str, NumType type);

int is_complex(double* re, double* im);


#endif // TOLLS_H