#ifndef UTIL_H
#define UTIL_H


typedef enum 
{
    INT_TYPE,
    DOUBLE_TYPE
} NumType;


int read_num(void* str, NumType type);

int is_complex(double* re, double* im);


#endif // UTIL_H