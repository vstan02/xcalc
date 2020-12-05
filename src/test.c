#include <gtk/gtk.h>

#include "core/test.h"

int main(int argc, char** argv) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func(TEST_TOKEN_PATH, test_token);
    g_test_add_func(TEST_EXPRESSION_PATH, test_expression);
    g_test_add_func(TEST_LEXER_PATH, test_lexer);
    g_test_add_func(TEST_INTERPRETER_PATH, test_interpreter);
    g_test_add_func(TEST_CALCULATOR_PATH, test_calculator);
    return g_test_run();
}
