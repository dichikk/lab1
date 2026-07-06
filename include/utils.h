#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include "poly_funcs.h"

int square_int(int x);
int abs_int(int x);
complex_num conjugate_complex(complex_num c);
complex_num square_mod_complex(complex_num c);

int is_even(int x);
int is_positive(int x);
int real_positive(complex_num c);
int imag_positive(complex_num c);

void clear_stdin(void);
int read_array_size(size_t *out);
int read_index(size_t *out, size_t count, const char *prompt);
int store_result(poly_arr* mass[], size_t *count, poly_arr *result);

#endif