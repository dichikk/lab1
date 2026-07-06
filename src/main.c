#include <stdio.h>
#include <stdlib.h>
#include "poly_funcs.h"
#include "text_blocks.h"
#include "sys_funcs.h"
#include "utils.h"

#define MAX_CAPACITY 64

int main(void)
{
    poly_arr* arr_storage[MAX_CAPACITY] = {0};
    size_t count = 0;
    int choice = 0;
    while (1) 
    {
        main_operations_text();
        if (scanf("%d", &choice) != 1)
        {
            clear_stdin();
            continue;
        }
        if (choice == 0) break;
        clear_stdin();
        if (choice == 1 || choice == 2)
        {
            if (count >= MAX_CAPACITY)
            {
                printf("Хранилище переполнено\n");
                continue;
            }
            size_t user_size;
            printf("Размер массива: ");
            if (!read_array_size(&user_size)) continue;
            if (choice == 1)
            {
                arr_storage[count] = create_empty_int_array(user_size);
                printf("Введите %zu целых чисел: ", user_size);
                int correct_wr = 1;
                for (size_t i = 0; i < user_size; i++)
                {
                    int value;
                    if(scanf("%d", &value)!= 1)
                    {
                        correct_wr = 0;
                        break;                    
                    }
                    set_int_by_index(arr_storage[count], i, value);
                }
                if (!correct_wr)
                {
                    printf("Ошибка ввода чисел\n");
                    free_array(arr_storage[count]);
                    clear_stdin();
                    continue;
                }
            } 
            else
            {
                arr_storage[count] = create_empty_complex_array(user_size);
                printf("Введите %zu комплексных чисел (real imag): ", user_size);
                int correct_wr = 1;
                for (size_t i = 0; i < user_size; i++)
                {
                    complex_num value;
                    if (scanf("%lf %lf", &value.real, &value.imag) != 2)
                    {
                        correct_wr = 0;
                        break;
                    }
                    set_complex_by_index(arr_storage[count], i, value);
                }
                if (!correct_wr)
                {
                    printf("Ошибка ввода чисел\n");
                    free_array(arr_storage[count]);
                    clear_stdin();
                    continue;
                }
            }
            if (arr_storage[count])
            {
                printf("Массив #%zu создан: ", count + 1);
                char* temp_str = serialize(arr_storage[count]);
                printf("%s\n", temp_str);
                free(temp_str);
                count++;
            } 
            else
            {
                printf("Ошибка создания массива\n");
            }
        }
        else if (choice == 3)
        {
            if (count == 0)
            {
                printf("Нет массивов\n");
                continue;
            }
            for(size_t i = 0; i < count; i++)
            {
                printf("Массив #%zu: ", i+1);
                char* temp_str = serialize(arr_storage[i]);
                printf("%s\n", temp_str);
                free(temp_str);
            }
        }
        else if (choice == 4)
        {
            if (count == 0)
            {
                printf("Нет массивов\n");
                continue;
            }
            size_t index;
            if (!read_index(&index, count, "Номер для удаления: ")) continue;
            free_array(arr_storage[index - 1]);
            for (size_t i = index - 1; i + 1 < count; i++) arr_storage[i] = arr_storage[i + 1];
            arr_storage[count - 1] = NULL;
            count--;
            printf("Массив удален\n");
        }
        else if (choice == 5)
        {
            if (count < 2)
            {
                printf("Нужно минимум 2 массива\n");
                continue;
            }
            size_t index1, index2;
            if (!read_index(&index1, count, "Первый массив: ")) continue;
            if (!read_index(&index2, count, "Второй массив: ")) continue;
            poly_arr *arr1 = arr_storage[index1 - 1], *arr2 = arr_storage[index2 - 1];
            if (get_type(arr1) != get_type(arr2))
            {
                printf("Типы массивов не совпадают\n");
            } 
            else
            {
                store_result(arr_storage, &count, array_concat(arr1, arr2));
            }
        }
        else if (choice == 6)
        {
            if (count == 0)
            {
                printf("Нет массивов\n");
                continue;
            }
            size_t index;
            if (!read_index(&index, count, "Номер массива: ")) continue;
            poly_arr* arr = arr_storage[index - 1];
            poly_arr* result = NULL;
            int operation_num;
            if (get_type(arr) == int_arr_type)
            {
                printf("1. Квадрат  2. Модуль\nВыбор: ");
                if (scanf("%d", &operation_num) != 1)
                {
                    clear_stdin();
                    continue;
                }
                if (operation_num == 1) result = array_map(arr, (void*)square_int);
                else if (operation_num == 2) result = array_map(arr, (void*)abs_int);
            } 
            else
            {
                printf("1. Сопряжение  2. Квадрат модуля\nВыбор: ");
                if (scanf("%d", &operation_num) != 1)
                {
                    clear_stdin();
                    continue;
                }
                if (operation_num == 1) result = array_map(arr, (void*)conjugate_complex);
                else if (operation_num == 2) result = array_map(arr, (void*)square_mod_complex);
            }
            store_result(arr_storage, &count, result);
            clear_stdin();
        }
        else if (choice == 7)
        {
            if (count == 0)
            {
                printf("Нет массивов\n");
                continue;
            }
            size_t index;
            if (!read_index(&index, count, "Номер массива: ")) continue;
            poly_arr* arr = arr_storage[index - 1];
            poly_arr* result = NULL;
            int predicate_num;
            if (get_type(arr) == int_arr_type)
            {
                printf("1. Чётные  2. Положительные\nВыбор: ");
                if (scanf("%d", &predicate_num) != 1)
                {
                    clear_stdin();
                    continue;
                }
                if (predicate_num == 1) result = array_where(arr, (void*)is_even);
                else if (predicate_num == 2) result = array_where(arr, (void*)is_positive);
            } 
            else 
            {
                printf("1. Re > 0  2. Im > 0\nВыбор: ");
                if (scanf("%d", &predicate_num) != 1)
                {
                    clear_stdin();
                    continue;
                }
                if (predicate_num == 1) result = array_where(arr, (void*)real_positive);
                else if (predicate_num == 2) result = array_where(arr, (void*)imag_positive);
            }
            store_result(arr_storage, &count, result);
            clear_stdin();
        }
        else 
        {
            printf("Неверный пункт меню\n");
        }
    }
    for (size_t i = 0; i < count; i++) free_array(arr_storage[i]);
    return 0;
}

