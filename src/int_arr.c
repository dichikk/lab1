#include "../include/poly_arr.h"
#include <string.h>

static arr_operations* int_ops = NULL;

arr_operations* create_int_operations()
{
    arr_operations* ops = (arr_operations*)malloc(sizeof(arr_operations));
    if (!ops) return NULL;
    ops->get_elem_size = get_int_size;
    ops->concat = int_concat;
    ops->map    = int_map;
    ops->where  = int_where;
    ops->resize = int_resize;
    ops->serialize = serialize_int_array;
    return ops;
}

arr_operations* get_int_operations()
{
    if (!int_ops)
    {
        int_ops = create_int_operations();
    }
    return int_ops;
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
    arr->length = length;
    arr->operations = get_int_operations();
    return arr;
}

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
    memcpy(arr->data, data, length * sizeof(int));
    arr->operations = get_int_operations();
    arr->length = length;
    return arr;
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

char* serialize_int_array(poly_arr* arr)
{
    if(!arr) return NULL;
    size_t buf_size = 1 + (13)* get_length(arr) + 2;
    char* buffer = (char*)malloc(buf_size);
    int elem;
    size_t offset = 0;
    offset += sprintf(buffer+offset, "[");
    for(size_t i = 0; i < get_length(arr); i++)
    {
        get_int_by_index(arr, i, &elem);
        if(i > 0) offset+= sprintf(buffer+offset, ", ");
        offset += sprintf(buffer+offset, "%d", elem);         
    }
    offset+=sprintf(buffer + offset, "]");
    return buffer;
}

void int_resize(poly_arr* arr, size_t new_length)
{
    if(!arr) return;
    if (new_length == 0) 
    {
        free(arr->data);
        arr->data = NULL;
        arr->length = 0;
        return;
    }
    int* temp_data = (int*)realloc(arr->data, new_length*sizeof(int));
    if(!temp_data) return;
    if(new_length > arr->length)
    {
        for(size_t i = arr->length; i < new_length; i++)
            temp_data[i] = 0;
    }
    arr->data = temp_data;
    arr->length = new_length;   
}

size_t get_int_size(void)
{
    return sizeof(int);
}

int get_int_by_index(poly_arr* arr, size_t index, int* out_value)
{
    if (!arr || index >= arr->length || !out_value) return 0;
    *out_value = ((int*)arr->data)[index];
    return 1;
}
int set_int_by_index(poly_arr* arr, size_t index, int value)
{
    if(!arr || index >= arr->length) return 0;
    ((int*)arr->data)[index] = value;
    return 1;
}
