#include <gtk/gtk.h>

#include "core/test.h"
#include "gui_tests.h"

void test_gui_all(int argc, char** argv) {
    gtk_init(&argc, &argv);
    g_test_add_func(TEST_SIZE_PATH, test_size);
    g_test_add_func(TEST_WINDOW_PATH, test_window);
}
