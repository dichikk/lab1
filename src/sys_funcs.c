#include <stdio.h>
#include <stdlib.h>
#include <poly_funcs.h>
#include <sys_funcs.h>


int clear_input()
{
    int c, counter = 0;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        counter++;
    }
    return counter;
}

void clear_screen() 
{
    system("clear");
}

size_t get_complex_buffer_size(poly_arr* arr)
{
    complex_num elem;
    size_t total = 1; 
    for (size_t i = 0; i < get_length(arr); i++)
    {
        int needed_for_elem;
        get_complex_by_index(arr, i, &elem);
        if (i > 0) total += 2;
        if (elem.imag >= 0)
            needed_for_elem = snprintf(NULL, 0, "%.2f+%.2fi", elem.real, elem.imag);
        else needed_for_elem = snprintf(NULL, 0, "%.2f%.2fi",  elem.real, elem.imag);
        if (needed_for_elem < 0) return 0;
        total += (size_t)needed_for_elem;
    }
    total+=2;
    return total;
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

char* serialize(poly_arr* arr)
{
    if(!arr) return NULL;
    if(get_type(arr) == int_arr_type)
        return serialize_int_array(arr);
    else return serialize_complex_array(arr);
}

