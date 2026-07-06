#include "poly_funcs.h"
#include <string.h>

typedef struct
{
    poly_arr* (*concat)(poly_arr* arr1, poly_arr* arr2);
    poly_arr* (*map)(poly_arr* arr, void* function);
    poly_arr* (*where)(poly_arr* arr, void* predicate);
} arr_operations;

struct polyarr
{
    void*          data;
    size_t         length;
    arr_type    type;
    arr_operations* operations;
};


poly_arr* create_int_array(int* data, size_t length)
{
    if (data == NULL || length == 0) return NULL;
    poly_arr* arr = (poly_arr*)malloc(sizeof(poly_arr));
    if (!arr) return NULL;
    arr->data = malloc(length * sizeof(int));
    if (!arr->data)
    {
        free(arr);
        return NULL;
    }
    arr->operations = (arr_operations*)malloc(sizeof(arr_operations));
    if (!arr->operations)
    {
        free(arr);
        return NULL;
    }
    memcpy(arr->data, data, length * sizeof(int));
    arr->length   = length;
    arr->type = int_arr_type;
    arr->operations->concat = int_concat;
    arr->operations->map    = int_map;
    arr->operations->where  = int_where;
    return arr;
}

poly_arr* create_complex_array(complex_num* data, size_t length) 
{
    if (data == NULL || length == 0) return NULL;
    poly_arr* arr = (poly_arr*)malloc(sizeof(poly_arr));
    if (!arr) return NULL;
    arr->data = malloc(length * sizeof(complex_num));
    if (!arr->data)
    {
        free(arr);
        return NULL;
    }
    arr->operations = (arr_operations*)malloc(sizeof(arr_operations));
    if (!arr->operations)
    {
        free(arr);
        return NULL;
    }
    memcpy(arr->data, data, length * sizeof(complex_num));
    arr->length   = length;
    arr->type = complex_arr_type;
    arr->operations->concat = complex_concat;
    arr->operations->map    = complex_map;
    arr->operations->where  = complex_where;
    return arr;
}


poly_arr* int_concat(poly_arr* arr1, poly_arr* arr2)
{
    if (!arr1 || !arr2 || !arr1->data || !arr2->data) return NULL;
    size_t new_length = arr1->length + arr2->length;
    int* new_data = (int*)malloc(new_length * sizeof(int));
    if (!new_data) return NULL;
    memcpy(new_data, arr1->data, arr1->length * sizeof(int));
    memcpy(new_data + arr1->length, arr2->data, arr2->length * sizeof(int));
    poly_arr* result = create_int_array(new_data, new_length);
    free(new_data);
    return result;
}

poly_arr* complex_concat(poly_arr* arr1, poly_arr* arr2) 
{
    if (!arr1 || !arr2 || !arr1->data || !arr2->data) return NULL;
    size_t new_length = arr1->length + arr2->length;
    complex_num* new_data = (complex_num*)malloc(new_length * sizeof(complex_num));
    if (!new_data) return NULL;
    memcpy(new_data, arr1->data, arr1->length * sizeof(complex_num));
    memcpy(new_data + arr1->length, arr2->data, arr2->length * sizeof(complex_num));
    poly_arr* result = create_complex_array(new_data, new_length);
    free(new_data);
    return result;
}

poly_arr* array_concat(poly_arr* arr1, poly_arr* arr2)
{
    if (!arr1 || !arr2)
    {
        printf("Ошибка: один из массивов не существует\n");
        return NULL;
    }
    return arr1->operations->concat(arr1, arr2);
}

poly_arr* int_map(poly_arr* arr, void* function)
{
    if (!arr || !arr->data || !function) return NULL;
    int (*f)(int) = (int (*)(int))function;
    int* arg_data = (int*)arr->data;
    int* new_data = (int*)malloc(arr->length * sizeof(int));
    if (!new_data) return NULL;
    for (size_t i = 0; i < arr->length; i++)
    {
        new_data[i] = f(arg_data[i]);
    }
    poly_arr* result = create_int_array(new_data, arr->length);
    free(new_data);
    return result;
}

poly_arr* complex_map(poly_arr* arr, void* function) 
{
    if (!arr || !arr->data || !function) return NULL;
    complex_num (*f)(complex_num) = (complex_num (*)(complex_num))function;
    complex_num* arg_data = (complex_num*)arr->data;
    complex_num* new_data = (complex_num*)malloc(arr->length * sizeof(complex_num));
    if (!new_data) return NULL;
    for (size_t i = 0; i < arr->length; i++)
    {
        new_data[i] = f(arg_data[i]);
    }
    poly_arr* result = create_complex_array(new_data, arr->length);
    free(new_data);
    return result;
}

poly_arr* array_map(poly_arr* arr, void* function)
{
    if (!arr || !function) return NULL;
    return arr->operations->map(arr, function);
}

poly_arr* int_where(poly_arr* arr, void* predicate) 
{
    if (!arr || !arr->data || !predicate) return NULL;
    int (*p)(int) = (int (*)(int))predicate;
    int* arg_data = (int*)arr->data;
    size_t count = 0;
    for (size_t i = 0; i < arr->length; i++)
    {
        if (p(arg_data[i])) count++;
    }
    if (count == 0) return NULL;
    int* new_data = (int*)malloc(count * sizeof(int));
    if (!new_data) return NULL;
    size_t index = 0;
    for (size_t i = 0; i < arr->length; i++)
    {
        if (p(arg_data[i])) new_data[index++] = arg_data[i];
    }
    poly_arr* result = create_int_array(new_data, count);
    free(new_data);
    return result;
}

poly_arr* complex_where(poly_arr* arr, void* predicate)
{
    if (!arr || !arr->data || !predicate) return NULL;
    int (*p)(complex_num) = (int (*)(complex_num))predicate;
    complex_num* arg_data = (complex_num*)arr->data;
    size_t count = 0;
    for (size_t i = 0; i < arr->length; i++)
    {
        if (p(arg_data[i])) count++;
    }
    if (count == 0) return NULL;
    complex_num* new_data = (complex_num*)malloc(count * sizeof(complex_num));
    if (!new_data) return NULL;
    size_t index = 0;
    for (size_t i = 0; i < arr->length; i++)
    {
        if (p(arg_data[i])) new_data[index++] = arg_data[i];
    }
    poly_arr* result = create_complex_array(new_data, count);
    free(new_data);
    return result;
}

poly_arr* array_where(poly_arr* arr, void* predicate)
{
    if (!arr || !predicate) return NULL;
    return arr->operations->where(arr, predicate);
}

void free_array(poly_arr* arr)
{
    if (!arr) return;
    free(arr->data);
    free (arr->operations);
    free(arr);
}

poly_arr* create_empty_int_array(size_t length)
{
    poly_arr* arr = (poly_arr*)malloc(sizeof(poly_arr));
    if (!arr) return NULL;
    arr->data = malloc(length * sizeof(int));
    if (!arr->data)
    {
        free(arr);
        return NULL;
    }
    arr->operations = (arr_operations*)malloc(sizeof(arr_operations));
    if (!arr->operations)
    {
        free(arr->data);
        free(arr);
        return NULL;
    }
    arr->type = int_arr_type;
    arr->length   = length;
    arr->operations->concat = int_concat;
    arr->operations->map    = int_map;
    arr->operations->where  = int_where;
    return arr;
}
poly_arr* create_empty_complex_array(size_t length)
{
    poly_arr* arr = (poly_arr*)malloc(sizeof(poly_arr));
    if (!arr) return NULL;
    arr->data = malloc(length * sizeof(complex_num));
    if (!arr->data)
    {
        free(arr);
        return NULL;
    }
    arr->operations = (arr_operations*)malloc(sizeof(arr_operations));
    if (!arr->operations)
    {
        free(arr->data);
        free(arr);
        return NULL;
    }
    arr->type = complex_arr_type;
    arr->length   = length;
    arr->operations->concat = complex_concat;
    arr->operations->map    = complex_map;
    arr->operations->where  = complex_where;
    return arr;
}



size_t get_length(poly_arr *arr)
{
    return (arr) ? arr->length : 0;
}

int get_int_by_index(poly_arr* arr, size_t index, int* out_value)
{
    if (!arr || index >= arr->length || !out_value) return 0;
    *out_value = ((int*)arr->data)[index];
    return 1;
}
int get_complex_by_index(poly_arr* arr, size_t index, complex_num* out_value)
{
    if (!arr || index >= arr->length || !out_value) return 0;
    *out_value = ((complex_num*)arr->data)[index];
    return 1;
}
int set_int_by_index(poly_arr* arr, size_t index, int value)
{
    if(!arr || index >= arr->length) return 0;
    ((int*)arr->data)[index] = value;
    return 1;
}
int set_complex_by_index(poly_arr* arr, size_t index, complex_num value)
{
    if(!arr || index >= arr->length) return 0;
    ((complex_num*)arr->data)[index] = value;
    return 1;
}

arr_type get_type(poly_arr* arr)
{
    return arr->type;
}



void resize(poly_arr* arr, size_t new_length)
{
    if(!arr) return;
    size_t elem_size = (get_type(arr) == int_arr_type)? sizeof(int) : sizeof(complex_num);
    void* temp_data = realloc(arr->data, new_length*elem_size);
    if(!temp_data)
        return;
    arr->length = new_length;
    arr->data = temp_data;
}