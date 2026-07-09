#include "../include/poly_arr.h"
#include "../include/sys_funcs.h"
#include <string.h>


static arr_operations* complex_ops = NULL;

arr_operations* create_complex_operations()
{
    arr_operations* ops = (arr_operations*)malloc(sizeof(arr_operations));
    if (!ops) return NULL;
    ops->get_elem_size = get_complex_size;
    ops->concat = complex_concat;
    ops->map    = complex_map;
    ops->where  = complex_where;
    ops->resize = complex_resize;
    ops->serialize = serialize_complex_array;
    return ops;
}

arr_operations* get_complex_operations()
{
    if (!complex_ops)
    {
        complex_ops = create_complex_operations();
    }
    return complex_ops;
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
    arr->length = length;
    arr->operations = get_complex_operations();
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
    memcpy(arr->data, data, length * sizeof(complex_num));
    arr->length = length;
    arr->operations = get_complex_operations();
    return arr;
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

char* serialize_complex_array(poly_arr* arr)
{        
    if(!arr) return NULL;
    char* buffer = (char*)malloc(get_complex_buffer_size(arr));
    complex_num elem;
    size_t offset = 0;
    offset += sprintf(buffer + offset, "[");
    for (size_t i = 0; i< get_length(arr); i++)
    {
        get_complex_by_index(arr, i, &elem);
        if(i>0) offset+=sprintf(buffer+ offset, ", ");
        if(elem.imag < 0)
            offset += sprintf(buffer + offset, "%.2f%.2fi", elem.real, elem.imag);
        else offset += sprintf(buffer + offset, "%.2f+%.2fi", elem.real, elem.imag);
    }
    offset+=sprintf(buffer + offset, "]");
    return buffer;
}

void complex_resize(poly_arr* arr, size_t new_length)
{
    if(!arr) return;
    if (new_length == 0) 
    {
        free(arr->data);
        arr->data = NULL;
        arr->length = 0;
        return;
    }
    complex_num zero = {0,0};
    complex_num* temp_data = (complex_num*)realloc(arr->data, new_length*sizeof(complex_num));
    if(!temp_data) return;
    if(new_length > arr->length)
    {
        for(size_t i = arr->length; i < new_length; i++)
            temp_data[i] = zero;
    }
    arr->data = temp_data;
    arr->length = new_length;   
}

size_t get_complex_size(void)
{
    return sizeof(complex_num);
}

int get_complex_by_index(poly_arr* arr, size_t index, complex_num* out_value)
{
    if (!arr || index >= arr->length || !out_value) return 0;
    *out_value = ((complex_num*)arr->data)[index];
    return 1;
}

int set_complex_by_index(poly_arr* arr, size_t index, complex_num value)
{
    if(!arr || index >= arr->length) return 0;
    ((complex_num*)arr->data)[index] = value;
    return 1;
}
