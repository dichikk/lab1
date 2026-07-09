#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assertions.h>
#include <poly_funcs.h>
#include <sys_funcs.h>
#include "testing.h"
#include "utils.h"

TEST(test_create_int_array)
{
    {
        int data[] = {1, 2, 3, 4, 5};
        poly_arr* arr = create_int_array(data, 5);
        assert(arr != NULL);
        assert(get_length(arr) == 5);
        int value;
        assert(get_int_by_index(arr, 0, &value) && value == 1);
        assert(get_int_by_index(arr, 1, &value) && value == 2);
        assert(get_int_by_index(arr, 2, &value) && value == 3);
        assert(get_int_by_index(arr, 3, &value) && value == 4);
        assert(get_int_by_index(arr, 4, &value) && value == 5);
        assert(get_operations(arr) == get_int_operations());
        free_array(arr);
    }
    
    {
        int data[] = {10, 20, 30};
        poly_arr* arr = create_int_array(data, 3);
        assert(arr != NULL);
        assert(get_length(arr) == 3);
        free_array(arr);
    }
    
    {
        poly_arr* arr = create_int_array(NULL, 5);
        assert(arr == NULL);
    }
    
    {
        int data[] = {1, 2, 3};
        poly_arr* arr = create_int_array(data, 0);
        assert(arr == NULL);
    }
}

TEST(test_create_complex_array) 
{
    {
        complex_num data[] = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
        poly_arr* arr = create_complex_array(data, 3);
        assert(arr != NULL);
        assert(get_length(arr) == 3);
        complex_num value;
        assert(get_complex_by_index(arr, 0, &value) && value.real == 1.0 && value.imag == 2.0);
        assert(get_complex_by_index(arr, 1, &value) && value.real == 3.0 && value.imag == 4.0);
        assert(get_complex_by_index(arr, 2, &value) && value.real == 5.0 && value.imag == 6.0);
        assert(get_operations(arr) == get_complex_operations());
        free_array(arr);
    }
    
    {
        poly_arr* arr = create_complex_array(NULL, 3);
        assert(arr == NULL);
        complex_num data[] = {{1.0, 2.0}};
        arr = create_complex_array(data, 0);
        assert(arr == NULL);
    }
}

TEST(test_int_concat)
{
    {
        int data1[] = {1, 2, 3};
        int data2[] = {4, 5, 6};
        poly_arr* arr1 = create_int_array(data1, 3);
        poly_arr* arr2 = create_int_array(data2, 3);
        poly_arr* result = int_concat(arr1, arr2);
        assert(result != NULL);
        assert(get_length(result) == 6);
        int value;
        assert(get_int_by_index(result, 0, &value) && value == 1);
        assert(get_int_by_index(result, 1, &value) && value == 2);
        assert(get_int_by_index(result, 2, &value) && value == 3);
        assert(get_int_by_index(result, 3, &value) && value == 4);
        assert(get_int_by_index(result, 4, &value) && value == 5);
        assert(get_int_by_index(result, 5, &value) && value == 6);
        free_array(arr1);
        free_array(arr2);
        free_array(result);
    }

    {
        int data1[] = {1, 2};
        int data2[] = {3, 4};
        poly_arr* arr1 = create_int_array(data1, 2);
        poly_arr* arr2 = create_int_array(data2, 2);
        poly_arr* result = int_concat(arr1, arr2);
        
        assert(result != NULL);
        assert(get_length(result) == 4);
        
        free_array(arr1);
        free_array(arr2);
        free_array(result);
    }
    
    {
        poly_arr* result = int_concat(NULL, NULL);
        assert(result == NULL);
        
        int data[] = {1, 2, 3};
        poly_arr* arr = create_int_array(data, 3);
        result = int_concat(arr, NULL);
        assert(result == NULL);
        free_array(arr);
    }
}

TEST(test_complex_concat)
{
    {
        complex_num data1[] = {{1.0, 1.0}, {2.0, 2.0}};
        complex_num data2[] = {{3.0, 3.0}, {4.0, 4.0}};
        poly_arr* arr1 = create_complex_array(data1, 2);
        poly_arr* arr2 = create_complex_array(data2, 2);
        poly_arr* result = complex_concat(arr1, arr2);
        assert(result != NULL);
        assert(get_length(result) == 4);
        complex_num value;
        assert(get_complex_by_index(result, 0, &value) && value.real == 1.0 && value.imag == 1.0);
        assert(get_complex_by_index(result, 1, &value) && value.real == 2.0 && value.imag == 2.0);
        assert(get_complex_by_index(result, 2, &value) && value.real == 3.0 && value.imag == 3.0);
        assert(get_complex_by_index(result, 3, &value) && value.real == 4.0 && value.imag == 4.0);
        
        free_array(arr1);
        free_array(arr2);
        free_array(result);
    }
}

TEST(test_array_concat)
{
    {
        int data1[] = {1, 2, 3};
        int data2[] = {4, 5, 6};
        poly_arr* arr1 = create_int_array(data1, 3);
        poly_arr* arr2 = create_int_array(data2, 3);
        poly_arr* result = array_concat(arr1, arr2);
        assert(result != NULL);
        assert(get_length(result) == 6);
        free_array(arr1);
        free_array(arr2);
        free_array(result);
    }
 
    {
        poly_arr* result = array_concat(NULL, NULL);
        assert(result == NULL);
    }
}

TEST(test_int_map)
{
    {
        int data[] = {1, 2, 3, 4, 5};
        poly_arr* arr = create_int_array(data, 5);
        poly_arr* result = int_map(arr, (void*)square_int);
        assert(result != NULL);
        assert(get_length(arr) == 5);
        int value;
        assert(get_int_by_index(result, 0, &value) && value == 1);
        assert(get_int_by_index(result, 1, &value) && value == 4);
        assert(get_int_by_index(result, 2, &value) && value == 9);
        assert(get_int_by_index(result, 3, &value) && value == 16);
        assert(get_int_by_index(result, 4, &value) && value == 25);
        free_array(arr);
        free_array(result);
    }
    
    {
        int data[] = {-5, -3, 0, 2, 4};
        poly_arr* arr = create_int_array(data, 5);
        poly_arr* result = int_map(arr, (void*)abs_int);
        assert(result != NULL);
        int value;
        assert(get_int_by_index(result, 0, &value) && value == 5);
        assert(get_int_by_index(result, 1, &value) && value == 3);
        assert(get_int_by_index(result, 2, &value) && value == 0);
        assert(get_int_by_index(result, 3, &value) && value == 2);
        assert(get_int_by_index(result, 4, &value) && value == 4);
        free_array(arr);
        free_array(result);
    }
    
    {
        poly_arr* result = int_map(NULL, (void*)square_int);
        assert(result == NULL);
        int data[] = {1, 2, 3};
        poly_arr* arr = create_int_array(data, 3);
        result = int_map(arr, NULL);
        assert(result == NULL);
        free_array(arr);
    }
}

TEST(test_complex_map)
{
    {
        complex_num data[] = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
        poly_arr* arr = create_complex_array(data, 3);
        poly_arr* result = complex_map(arr, (void*)conjugate_complex);
        assert(result != NULL);
        assert(get_length(result) == 3);
        complex_num value;
        assert(get_complex_by_index(result, 0, &value) && value.real == 1.0 && value.imag == -2.0);
        assert(get_complex_by_index(result, 1, &value) && value.real == 3.0 && value.imag == -4.0);
        assert(get_complex_by_index(result, 2, &value) && value.real == 5.0 && value.imag == -6.0);
        free_array(arr);
        free_array(result);
    }
    
    {
        complex_num data[] = {{1.0, 2.0}, {3.0, 4.0}};
        poly_arr* arr = create_complex_array(data, 2);
        poly_arr* result = complex_map(arr, (void*)square_mod_complex);
        assert(result != NULL);
        assert(get_length(result) == 2);
        complex_num value;
        assert(get_complex_by_index(result, 0, &value) && value.real == 5.0 && value.imag == 0.0);
        assert(get_complex_by_index(result, 1, &value) && value.real == 25.0 && value.imag == 0.0);
        free_array(arr);
        free_array(result);
    }
}

TEST(test_array_map)
{
    {
        int data[] = {1, 2, 3};
        poly_arr* arr = create_int_array(data, 3);
        poly_arr* result = array_map(arr, (void*)square_int);
        assert(result != NULL);
        assert(get_length(result) == 3);
        free_array(arr);
        free_array(result);
    }
    
    {
        poly_arr* result = array_map(NULL, (void*)square_int);
        assert(result == NULL);
    }
}

TEST(test_int_where)
{
    {
        int data[] = {1, 2, 3, 4, 5, 6};
        poly_arr* arr = create_int_array(data, 6);
        poly_arr* result = int_where(arr, (void*)is_even);
        assert(result != NULL);
        assert(get_length(result) == 3);
        int value;
        assert(get_int_by_index(result, 0, &value) && value == 2);
        assert(get_int_by_index(result, 1, &value) && value == 4);
        assert(get_int_by_index(result, 2, &value) && value == 6);
        free_array(arr);
        free_array(result);
    }

    {
        int data[] = {-3, -2, -1, 0, 1, 2, 3};
        poly_arr* arr = create_int_array(data, 7);
        poly_arr* result = int_where(arr, (void*)is_positive);
        assert(result != NULL);
        assert(get_length(result) == 3);
        int value;
        assert(get_int_by_index(result, 0, &value) && value == 1);
        assert(get_int_by_index(result, 1, &value) && value == 2);
        assert(get_int_by_index(result, 2, &value) && value == 3);
        free_array(arr);
        free_array(result);
    }
    
    {
        int data[] = {-1, -2, -3, -4};
        poly_arr* arr = create_int_array(data, 4);
        poly_arr* result = int_where(arr, (void*)is_positive);
        
        assert(result == NULL);
        
        free_array(arr);
    }
    
    {
        poly_arr* result = int_where(NULL, (void*)is_even);
        assert(result == NULL);
        
        int data[] = {1, 2, 3};
        poly_arr* arr = create_int_array(data, 3);
        result = int_where(arr, NULL);
        assert(result == NULL);
        free_array(arr);
    }
}

TEST(test_complex_where) 
{
    {
        complex_num data[] = {{-1.0, 1.0}, {2.0, -3.0}, {-4.0, 5.0}, {6.0, 7.0}};
        poly_arr* arr = create_complex_array(data, 4);
        poly_arr* result = complex_where(arr, (void*)real_positive);
        assert(result != NULL);
        assert(get_length(result) == 2);
        complex_num value;
        assert(get_complex_by_index(result, 0, &value) && value.real == 2.0 && value.imag == -3.0);
        assert(get_complex_by_index(result, 1, &value) && value.real == 6.0 && value.imag == 7.0);
        free_array(arr);
        free_array(result);
    }
    
    {
        complex_num data[] = {{1.0, -1.0}, {2.0, 3.0}, {4.0, -5.0}, {6.0, 7.0}};
        poly_arr* arr = create_complex_array(data, 4);
        poly_arr* result = complex_where(arr, (void*)imag_positive);
        assert(result != NULL);
        assert(get_length(result) == 2);
        complex_num value;
        assert(get_complex_by_index(result, 0, &value) && value.real == 2.0 && value.imag == 3.0);
        assert(get_complex_by_index(result, 1, &value) && value.real == 6.0 && value.imag == 7.0);
        free_array(arr);
        free_array(result);
    }
}

TEST(test_array_where)
{
    {
        int data[] = {1, 2, 3, 4, 5};
        poly_arr* arr = create_int_array(data, 5);
        poly_arr* result = array_where(arr, (void*)is_even);
        assert(result != NULL);
        assert(get_length(result) == 2);
        free_array(arr);
        free_array(result);
    }
    
    {
        poly_arr* result = array_where(NULL, (void*)is_even);
        assert(result == NULL);
    }
}

TEST(test_serialize_int_array)
{
    {
        int data[] = {1, 2, 3, 4, 5};
        poly_arr* arr = create_int_array(data, 5);
        char* temp_data = serialize(arr);
        assert(strcmp("[1, 2, 3, 4, 5]", temp_data) == 0);
        free_array(arr);
        free(temp_data);
    }
}

TEST(test_serialize_complex_array) 
{
    {
        complex_num data[] = {{1.0, 2.0}, {3.0, -4.0}, {5.0, 6.0}};
        poly_arr* arr = create_complex_array(data, 3);
        char* temp_data = serialize(arr);
        assert(strcmp("[1.00+2.00i, 3.00-4.00i, 5.00+6.00i]", temp_data) == 0);
        free_array(arr);
        free(temp_data);
    }
}

TEST(test_free_array) 
{
    {
        assert(1 == 1);
    }
    {
        int data[] = {1, 2, 3};
        poly_arr* arr = create_int_array(data, 3);
        assert(arr != NULL);
        free_array(arr);
        assert(1 == 1);
    }
}

TEST(test_memory_leak_concat) 
{
    {
        int data1[] = {1, 2, 3};
        int data2[] = {4, 5, 6};
        poly_arr* arr1 = create_int_array(data1, 3);
        poly_arr* arr2 = create_int_array(data2, 3);
        poly_arr* result = array_concat(arr1, arr2);
        assert(result != NULL);
        free_array(arr1);
        free_array(arr2);
        free_array(result);
    }
}

TEST(test_memory_leak_map) 
{
    {
        int data[] = {1, 2, 3, 4, 5};
        poly_arr* arr = create_int_array(data, 5);
        poly_arr* result = array_map(arr, (void*)square_int);
        assert(result != NULL);
        free_array(arr);
        free_array(result);
    }
}

TEST(test_memory_leak_where) 
{
    {
        int data[] = {1, 2, 3, 4, 5, 6};
        poly_arr* arr = create_int_array(data, 6);
        poly_arr* result = array_where(arr, (void*)is_even);
        assert(result != NULL);
        free_array(arr);
        free_array(result);
    }
}

TEST(test_int_resize)
{
    {
        int data[] = {1, 2, 3};
        poly_arr* arr = create_int_array(data, 3);
        assert(arr != NULL);
        resize(arr, 5);
        assert(get_length(arr) == 5);
        int value;
        assert(get_int_by_index(arr, 0, &value) && value == 1);
        assert(get_int_by_index(arr, 1, &value) && value == 2);
        assert(get_int_by_index(arr, 2, &value) && value == 3);
        assert(get_int_by_index(arr, 3, &value) && value == 0); 
        assert(get_int_by_index(arr, 4, &value) && value == 0); 
        free_array(arr);
    }

    {
        int data[] = {10, 20, 30, 40, 50};
        poly_arr* arr = create_int_array(data, 5);
        assert(arr != NULL);
        resize(arr, 2);
        assert(get_length(arr) == 2);
        int value;
        assert(get_int_by_index(arr, 0, &value) && value == 10);
        assert(get_int_by_index(arr, 1, &value) && value == 20);
        assert(!get_int_by_index(arr, 2, &value));
        free_array(arr);
    }

    {
        int data[] = {1, 2};
        poly_arr* arr = create_int_array(data, 2);
        resize(arr, 0);
        assert(get_length(arr) == 0);
        free_array(arr);
    }
}

TEST(test_complex_resize)
{
    {
        complex_num data[] = {{1.0, 1.0}, {2.0, 2.0}};
        poly_arr* arr = create_complex_array(data, 2);
        assert(arr != NULL);
        resize(arr, 4);
        assert(get_length(arr) == 4);
        complex_num value;
        assert(get_complex_by_index(arr, 0, &value) && value.real == 1.0 && value.imag == 1.0);
        assert(get_complex_by_index(arr, 1, &value) && value.real == 2.0 && value.imag == 2.0);
        assert(get_complex_by_index(arr, 2, &value) && value.real == 0.0 && value.imag == 0.0);
        assert(get_complex_by_index(arr, 3, &value) && value.real == 0.0 && value.imag == 0.0);
        free_array(arr);
    }

    {
        complex_num data[] = {{1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}};
        poly_arr* arr = create_complex_array(data, 3);
        assert(arr != NULL);
        resize(arr, 1);
        assert(get_length(arr) == 1);
        complex_num value;
        assert(get_complex_by_index(arr, 0, &value) && value.real == 1.0 && value.imag == 1.0);
        assert(!get_complex_by_index(arr, 1, &value));
        free_array(arr);
    }
}

TEST_ENTRY_POINT