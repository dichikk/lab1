#ifndef SYS_FUNCS_H
#define SYS_FUNCS_H
int clear_input();
void clear_screen();
size_t get_buffer_size(poly_arr* arr);
char* serialize(poly_arr* arr);
char* serialize_int_array(poly_arr* arr);
char* serialize_complex_array(poly_arr* arr);
// poly_arr* deserialize_int_array(char* str);
// poly_arr* deserialize_complex_array(char* str);
#endif