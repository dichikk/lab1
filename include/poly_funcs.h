#ifndef POLY_FUNCS_H
#define POLY_FUNCS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    double real;
    double imag;
} complex_num;


typedef struct polyarr poly_arr;
typedef struct arr_operations arr_operations;

poly_arr* create_empty_int_array(size_t length);
poly_arr* create_int_array(int* data, size_t length);
poly_arr* int_map(poly_arr* arr, void* function);
poly_arr* int_concat(poly_arr* arr1, poly_arr* arr2);
poly_arr* int_where(poly_arr* arr, void* predicate);
char* serialize_int_array(poly_arr* arr);
void int_resize(poly_arr* arr, size_t new_length);
size_t get_int_size(void);

poly_arr* create_empty_complex_array(size_t length);
poly_arr* create_complex_array(complex_num* data, size_t length);
poly_arr* complex_map(poly_arr* arr, void* function);
poly_arr* complex_concat(poly_arr* arr1, poly_arr* arr2);
poly_arr* complex_where(poly_arr* arr, void* predicate);
char* serialize_complex_array(poly_arr* arr);
void complex_resize(poly_arr* arr, size_t new_length);
size_t get_complex_size(void);

int get_int_by_index(poly_arr* arr, size_t index, int* out_value);
int get_complex_by_index(poly_arr* arr, size_t index, complex_num* out_value);
int set_int_by_index(poly_arr* arr, size_t index, int value);
int set_complex_by_index(poly_arr* arr, size_t index, complex_num value);
arr_operations* get_int_operations(void);
arr_operations* get_complex_operations(void);
size_t get_length(poly_arr* arr);
arr_operations* get_operations(poly_arr* arr);

poly_arr* array_map(poly_arr* arr, void* function);
poly_arr* array_concat(poly_arr* arr1, poly_arr* arr2);
poly_arr* array_where(poly_arr* arr, void* predicate);
void resize(poly_arr* arr, size_t new_length);
char* serialize(poly_arr* arr);

void free_array(poly_arr* arr);

#endif