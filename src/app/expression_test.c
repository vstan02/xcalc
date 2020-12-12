#include <gtk/gtk.h>

#include "app_tests.h"
#include "expression.h"

static void test_expression_main(void);
static void test_expression_getters(void);

void test_expression(void) {
    test_expression_main();
    g_test_add_func(TEST_EXPRESSION_PATH "/getters", test_expression_getters);
}

static void test_expression_main(void) {
    Expression* expression = expression_create("test");
    g_assert_nonnull(expression);
    expression_destroy(expression);
}

static void test_expression_getters(void) {
    Expression* expression = expression_create("test");
    g_assert_cmpint(expression_get_size(expression), ==, 4);
    g_assert_cmpint(expression_get_char(expression, 1), ==, 'e');
    expression_destroy(expression);
}
