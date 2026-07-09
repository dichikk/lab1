#ifndef POLY_ARR_H
#define POLY_ARR_H

#include "poly_funcs.h"

struct arr_operations {
    size_t (*get_elem_size)(void);
    poly_arr* (*concat)(poly_arr* arr1, poly_arr* arr2);
    poly_arr* (*map)(poly_arr* arr, void* function);
    poly_arr* (*where)(poly_arr* arr, void* predicate);
    void (*resize)(poly_arr* arr, size_t new_length);
    char* (*serialize)(poly_arr* arr);
};

struct polyarr {
    void* data;
    size_t length;
    arr_operations* operations;
};


#endif