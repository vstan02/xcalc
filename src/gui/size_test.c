#include <gtk/gtk.h>

#include "gui_tests.h"
#include "size.h"

static void test_size_main(void);
static void test_size_fields(void);

void test_size(void) {
    test_size_main();
    g_test_add_func(TEST_SIZE_PATH "/fields", test_size_fields);
}

static void test_size_main(void) {
    Size* size = size_create(20, 20);
    g_assert_nonnull(size);
    size_destroy(size);
}

static void test_size_fields(void) {
    Size* size = size_create(20, 50);
    g_assert_cmpint(size->width, ==, 20);
    g_assert_cmpint(size->height, ==, 50);
    size_destroy(size);
}