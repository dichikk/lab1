#include "poly_arr.h"
#include <string.h>

size_t get_length(poly_arr *arr)
{
    return (arr) ? arr->length : 0;
}

size_t get_elem_size(poly_arr* arr)
{
    return arr->operations->get_elem_size();
}
poly_arr* array_map(poly_arr* arr, void* function)
{
    if (!arr || !function) return NULL;
    return arr->operations->map(arr, function);
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

poly_arr* array_where(poly_arr* arr, void* predicate)
{
    if (!arr || !predicate) return NULL;
    return arr->operations->where(arr, predicate);
}

void resize(poly_arr* arr, size_t new_length)
{
    if(!arr) return;
    arr->operations->resize(arr, new_length);
}

char* serialize(poly_arr* arr)
{
    if(!arr) return NULL;
    return arr->operations->serialize(arr);
}
arr_operations* get_operations(poly_arr* arr)
{
    return (arr) ? arr->operations : NULL;
}
void free_array(poly_arr* arr)
{
    if (!arr) return;
    free(arr->data);
    free(arr);
}