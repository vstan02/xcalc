#include <glib.h>

#include "app_tests.h"
#include "token.h"

static void test_token_token(void);
static void test_token_getters(void);

void test_token(void) {
    g_test_add_func(TEST_TOKEN_PATH "/token", test_token_token);
    g_test_add_func(TEST_TOKEN_PATH "/getters", test_token_getters);
}

static void test_token_token(void) {
    Token* token = token_create(TOKEN_NUMBER, 5);
    g_assert_nonnull(token);
    token_destroy(token);
}

static void test_token_getters(void) {
    Token* token = token_create(TOKEN_NUMBER, 5);
    g_assert_cmpint(token_get_type(token), ==, TOKEN_NUMBER);
    g_assert_cmpint(token_get_payload(token), ==, 5);
    token_destroy(token);
}
