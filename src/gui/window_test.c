#include <gtk/gtk.h>

#include "gui_tests.h"
#include "window.h"

static void test_window_main(void);

void test_window(void) {
    test_window_main();
}

static void test_window_main(void) {
    Window* window = window_create("Test", size_create(20, 20));
    g_assert_nonnull(window);
    window_destroy(window);
}
