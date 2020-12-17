#include <gtk/gtk.h>

#include "gui_tests.h"
#include "window.h"

static void test_window_window(void);

void test_window(void) {
    g_test_add_func(TEST_WINDOW_PATH "/window", test_window_window);
}

static void test_window_window(void) {
    Window* window = window_create("Test", size_create(20, 20));
    g_assert_nonnull(window);
    window_destroy(window);
}
