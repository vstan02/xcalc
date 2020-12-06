#include <gtk/gtk.h>

#include "core/test.h"
#include "interpreter.h"

static void test_interpreter_main(void);
static void test_interpreter_process(void);

void test_interpreter(void) {
    test_interpreter_main();
    g_test_add_func(TEST_INTERPRETER_PATH "/process", test_interpreter_process);
}

static void test_interpreter_main(void) {
    Interpreter* interpreter = interpreter_create("4 + 7");
    g_assert_nonnull(interpreter);
    interpreter_destroy(interpreter);
}

static void verify_expression_processing(char* exp, double result) {
    Interpreter* interpreter = interpreter_create(exp);
    g_assert_cmpfloat(interpreter_process(interpreter), ==, result);
    interpreter_destroy(interpreter);
}

static void test_interpreter_process(void) {
    verify_expression_processing("3", 3);
    verify_expression_processing("3 + 4 * 2", 11);
    verify_expression_processing("(3 + 4) * 2", 14);
}
