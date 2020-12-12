#include <gtk/gtk.h>

#include "core/test.h"
#include "gui_tests.h"

void test_gui_all(void) {
    g_test_add_func(TEST_SIZE_PATH, test_size);
    g_test_add_func(TEST_WINDOW_PATH, test_window);
}
