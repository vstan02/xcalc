#include <gtk/gtk.h>

#include "test.h"

int main(int argc, char** argv) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func(TEST_TOKEN_PATH, test_token);
    g_test_add_func(TEST_EXPRESSION_PATH, test_expression);
    return g_test_run();
}
