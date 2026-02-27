#ifndef FIELD_INFO_H
#define FIELD_INFO_H

#include <stddef.h>

typedef struct FieldInfo {
    size_t size;

    void (*add)(void* a, void* b, void* res);
    void (*mult)(void* a, void* b, void* res);
    void (*DerivativeOperationInCoef)(void* co, int degree, void* result);

    void (*print)(void* element);
} FieldInfo;

typedef struct Complex {
    double re;
    double im;
} Complex;

FieldInfo* GetIntFieldInfo();

FieldInfo* GetComplexFieldInfo();



#endif 