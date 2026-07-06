#ifndef TESTING_H
#define TESTING_H

#include <stddef.h>
#include "assertions.h"

typedef void (*test_func)(void);

void register_test(const char* name, test_func test);
void run_test();
int print_stats();
void cleanup_tests();
void inc_success();
void inc_fail();
int pop_fail();
int pop_success();

typedef struct _test
{
    const char* name;
    void (*test_func)(void);
    struct _test* next;
} _test;

#define TEST(test_name) \
    static void test_name##_test(void); \
    static void __attribute__((constructor)) test_name##_init(void) { \
        register_test(#test_name, test_name##_test); \
    } \
    static void test_name##_test(void)

#define TEST_ENTRY_POINT \
    int main(void) { \
        run_test(); \
        int result = print_stats(); \
        cleanup_tests(); \
        return result; \
    }

#endif