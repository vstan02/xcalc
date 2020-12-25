#include <gtk/gtk.h>

#include "app_tests.h"
#include "text.h"

static void test_text_text(void);
static void test_text_getters(void);

void test_text(void) {
    g_test_add_func(TEST_TEXT_PATH "/text", test_text_text);
    g_test_add_func(TEST_TEXT_PATH "/getters", test_text_getters);
}

static void test_text_text(void) {
    Text* text = text_create("test");
    g_assert_nonnull(text);
    text_destroy(text);
}

static void test_text_getters(void) {
    Text* text = text_create("test");
    g_assert_cmpint((uint8_t) text_get_size(text), ==, 4);
    g_assert_cmpint((uint8_t) text_get_char(text, 1), ==, 'e');
    text_destroy(text);
}
