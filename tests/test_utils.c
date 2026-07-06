#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assertions.h>
#include <poly_funcs.h>
#include <sys_funcs.h>
#include "testing.h"
#include "utils.h"

TEST(test_square_int)
{
    {
        int result = square_int(5);
        assert(result == 25);
    }
    
    {
        int result = square_int(-3);
        assert(result == 9);
    }
    
    {
        int result = square_int(0);
        assert(result == 0);
    }
    
    {
        int result = square_int(1);
        assert(result == 1);
    }
}

TEST(test_abs_int) 
{
    {
        int result = abs_int(42);
        assert(result == 42);
    }
    
    {
        int result = abs_int(-17);
        assert(result == 17);
    }
    
    {
        int result = abs_int(0);
        assert(result == 0);
    }
    
    {
        int result = abs_int(-2147483647);
        assert(result == 2147483647);
    }
}

TEST(test_conjugate_complex)
{
    {
        complex_num c = {3.0, 4.0};
        complex_num result = conjugate_complex(c);
        assert(result.real == 3.0);
        assert(result.imag == -4.0);
    }
    
    {
        complex_num c = {-2.5, -1.5};
        complex_num result = conjugate_complex(c);
        assert(result.real == -2.5);
        assert(result.imag == 1.5);
    }
    
    {
        complex_num c = {7.0, 0.0};
        complex_num result = conjugate_complex(c);
        assert(result.real == 7.0);
        assert(result.imag == 0.0);
    }
    
    {
        complex_num c = {0.0, -5.0};
        complex_num result = conjugate_complex(c);
        assert(result.real == 0.0);
        assert(result.imag == 5.0);
    }
}

TEST(test_square_mod_complex)
{
    {
        complex_num c = {3.0, 4.0};
        complex_num result = square_mod_complex(c);
        assert(result.real == 25.0);
        assert(result.imag == 0.0);
    }
    
    {
        complex_num c = {-2.0, -3.0};
        complex_num result = square_mod_complex(c);
        assert(result.real == 13.0);
        assert(result.imag == 0.0);
    }
    
    {
        complex_num c = {0.0, 0.0};
        complex_num result = square_mod_complex(c);
        assert(result.real == 0.0);
        assert(result.imag == 0.0);
    }
    
    {
        complex_num c = {1.5, 2.5};
        complex_num result = square_mod_complex(c);
        assert(result.real == 8.5);
        assert(result.imag == 0.0);
    }
}

TEST(test_is_even) 
{
    {
        int result = is_even(4);
        assert(result == 1);
    }
    
    {
        int result = is_even(7);
        assert(result == 0);
    }
    
    {
        int result = is_even(-6);
        assert(result == 1);
    }
    
    {
        int result = is_even(0);
        assert(result == 1);
    }
}

TEST(test_is_positive) 
{
    {
        int result = is_positive(10);
        assert(result == 1);
    }
    
    {
        int result = is_positive(-5);
        assert(result == 0);
    }
    
    {
        int result = is_positive(0);
        assert(result == 0);
    }
    
    {
        int result = is_positive(1000000);
        assert(result == 1);
    }
}

TEST(test_real_positive) {
    {
        complex_num c = {5.0, 3.0};
        int result = real_positive(c);
        assert(result == 1);
    }
    
    {
        complex_num c = {-2.0, 4.0};
        int result = real_positive(c);
        assert(result == 0);
    }
    
    {
        complex_num c = {0.0, 1.0};
        int result = real_positive(c);
        assert(result == 0);
    }
    
    {
        complex_num c = {0.001, -5.0};
        int result = real_positive(c);
        assert(result == 1);
    }
}

TEST(test_imag_positive) 
{
    {
        complex_num c = {3.0, 7.0};
        int result = imag_positive(c);
        assert(result == 1);
    }
    
    {
        complex_num c = {4.0, -3.0};
        int result = imag_positive(c);
        assert(result == 0);
    }
    
    {
        complex_num c = {1.0, 0.0};
        int result = imag_positive(c);
        assert(result == 0);
    }
    
    {
        complex_num c = {-5.0, 0.001};
        int result = imag_positive(c);
        assert(result == 1);
    }
}

TEST(test_array_map_with_utils) 
{
    {
        int data[] = {1, 2, 3, 4, 5};
        poly_arr* arr = create_int_array(data, 5);
        poly_arr* result = array_map(arr, (void*)square_int);
        assert(result != NULL);
        assert(get_length(result) == 5);
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
        int data[] = {-3, -2, -1, 0, 1};
        poly_arr* arr = create_int_array(data, 5);
        poly_arr* result = array_map(arr, (void*)abs_int);
        assert(result != NULL);
        assert(get_length(result) == 5);
        int value;
        assert(get_int_by_index(result, 0, &value) && value == 3);
        assert(get_int_by_index(result, 1, &value) && value == 2);
        assert(get_int_by_index(result, 2, &value) && value == 1);
        assert(get_int_by_index(result, 3, &value) && value == 0);
        assert(get_int_by_index(result, 4, &value) && value == 1);
        free_array(arr);
        free_array(result);
    }
}

TEST(test_array_where_with_utils) {
    {
        int data[] = {1, 2, 3, 4, 5, 6};
        poly_arr* arr = create_int_array(data, 6);
        poly_arr* result = array_where(arr, (void*)is_even);
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
        int data[] = {-5, -3, 0, 2, 4, 6};
        poly_arr* arr = create_int_array(data, 6);
        poly_arr* result = array_where(arr, (void*)is_positive);
        assert(result != NULL);
        assert(get_length(result) == 3);
        int value;
        assert(get_int_by_index(result, 0, &value) && value == 2);
        assert(get_int_by_index(result, 1, &value) && value == 4);
        assert(get_int_by_index(result, 2, &value) && value == 6);
        free_array(arr);
        free_array(result);
    }
}

TEST(test_complex_array_with_utils) {
    {
        complex_num data[] = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
        poly_arr* arr = create_complex_array(data, 3);
        poly_arr* result = array_map(arr, (void*)conjugate_complex);
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
        complex_num data[] = {{-1.0, 1.0}, {2.0, -3.0}, {-4.0, 5.0}, {6.0, 7.0}};
        poly_arr* arr = create_complex_array(data, 4);
        poly_arr* result = array_where(arr, (void*)real_positive);
        assert(result != NULL);
        assert(get_length(result) == 2);
        complex_num value;
        assert(get_complex_by_index(result, 0, &value) && value.real == 2.0 && value.imag == -3.0);
        assert(get_complex_by_index(result, 1, &value) && value.real == 6.0 && value.imag == 7.0);
        free_array(arr);
        free_array(result);
    }
}

TEST_ENTRY_POINT