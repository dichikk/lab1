#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "sys_funcs.h"
#include "poly_funcs.h"

#define MAX_MASS       64
#define MAX_ARRAY_SIZE 100000

int square_int(int x)
{
    return x * x;
}

int abs_int(int x) 
{
    return x < 0 ? -x : x;
}

complex_num conjugate_complex(complex_num c)
{
    return (complex_num){c.real, -c.imag};
}

complex_num square_mod_complex(complex_num c)
{
    return (complex_num){c.real*c.real + c.imag*c.imag, 0};
}

int is_even(int x)
{
    return x % 2 == 0;
}

int is_positive(int x)
{
    return x > 0;
}

int real_positive(complex_num c) 
{
    return c.real > 0;
}

int imag_positive(complex_num c) {
    return c.imag > 0;
}

void clear_stdin(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int read_array_size(size_t *out)
{
    int n_input;
    if (scanf("%d", &n_input) != 1)
    {
        clear_stdin();
        printf("Нужно ввести число\n");
        return 0;
    }
    clear_stdin();
    if (n_input <= 0) {
        printf("Размер должен быть положительным числом\n");
        return 0;
    }
    if (n_input > MAX_ARRAY_SIZE) {
        printf("Размер слишком большой (максимум %d)\n", MAX_ARRAY_SIZE);
        return 0;
    }
    *out = (size_t)n_input;
    return 1;
}

int read_index(size_t *out, size_t count, const char *prompt) 
{
    size_t index;
    printf("%s", prompt);
    if (scanf("%zu", &index) != 1 || index < 1 || index > count)
    {
        printf("Неверный номер\n");
        clear_stdin();
        return 0;
    }
    clear_stdin();
    *out = index;
    return 1;
}

int store_result(poly_arr* mass[], size_t *count, poly_arr *result)
{
    if (!result)
    {
        printf("Пустой результат (возможно, ни один элемент не подошёл)\n");
        return 0;
    }
    if (*count >= MAX_MASS)
    {
        printf("Хранилище переполнено, результат отброшен\n");
        free_array(result);
        return 0;
    }
    mass[*count] = result;
    printf("Результат сохранен как массив #%zu: ", *count + 1);
    char* temp_str = serialize(result);
    printf("%s", temp_str);
    free(temp_str);
    (*count)++;
    return 1;
}