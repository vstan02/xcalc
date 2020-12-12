#include <gtk/gtk.h>

#include "core/test.h"
#include "app_tests.h"

void test_app_all(void) {
    g_test_add_func(TEST_TOKEN_PATH, test_token);
    g_test_add_func(TEST_EXPRESSION_PATH, test_expression);
    g_test_add_func(TEST_LEXER_PATH, test_lexer);
    g_test_add_func(TEST_INTERPRETER_PATH, test_interpreter);
    g_test_add_func(TEST_CALCULATOR_PATH, test_calculator);
}
