#include <gtk/gtk.h>

#include "app_tests.h"
#include "interpreter.h"

static void test_interpreter_interpreter(void);
static void test_interpreter_process(void);

void test_interpreter(void) {
    g_test_add_func(TEST_INTERPRETER_PATH "/interpreter", test_interpreter_interpreter);
    g_test_add_func(TEST_INTERPRETER_PATH "/process", test_interpreter_process);
}

static void test_interpreter_interpreter(void) {
    Interpreter* interpreter = interpreter_create("4 + 7");
    g_assert_nonnull(interpreter);
    interpreter_destroy(interpreter);
}

static void verify_expression_processing(char* exp, double result) {
    Interpreter* interpreter = interpreter_create(exp);
    double res;
    interpreter_process(interpreter, &res);
    g_assert_cmpfloat(res, ==, result);
    interpreter_destroy(interpreter);
}

static void test_interpreter_process(void) {
    verify_expression_processing("3", 3);
    verify_expression_processing("3 + 4 * 2", 11);
    verify_expression_processing("(3 + 4) * 2", 14);
}
