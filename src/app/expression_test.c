#include <gtk/gtk.h>

#include "core/test.h"
#include "expression.h"

static void test_expression_main(void);
static void test_expression_getters(void);

void test_expression(void) {
    test_expression_main();
    g_test_add_func(TEST_EXPRESSION_PATH "/getters", test_expression_getters);
}

static void test_expression_main(void) {
    Expression* expression = Expression_create("test");
    g_assert_nonnull(expression);
    Expression_destroy(expression);
}

static void test_expression_getters(void) {
    Expression* expression = Expression_create("test");
    g_assert_cmpint(expression->get_size(expression), ==, 4);
    Expression_destroy(expression);
}
