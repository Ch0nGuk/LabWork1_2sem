#ifndef FIELD_INFO_H
#define FIELD_INFO_H

#include <stddef.h>

typedef enum 
{
    INT_TYPE,
    DOUBLE_TYPE
} NumType;

// Утилиты для работы со строками и числами
static char* strip_str(char* str);
int read_num(void* str, NumType type);

typedef struct FieldInfo {
    size_t size;

    void (*add)(void* a, void* b, void* res);
    void (*mult)(void* a, void* b, void* res);
    void (*derivop)(void* co, int degree, void* result);

    void (*print)(void* element);
    int (*read)(void *element);
} FieldInfo;

typedef struct Complex {
    double re;
    double im;
} Complex;

FieldInfo* get_int_field_info();
FieldInfo* get_complex_field_info();

#endif