#include <gtk/gtk.h>

#include "core/test.h"
#include "token.h"

static void test_token_main(void);
static void test_token_getters(void);

void test_token(void) {
    test_token_main();
    g_test_add_func(TEST_TOKEN_PATH "/getters", test_token_getters);
}

static void test_token_main(void) {
    Token* token = Token_create(NUMBER, 5);
    g_assert_nonnull(token);
    Token_destroy(token);
}

static void test_token_getters(void) {
    Token* token = Token_create(NUMBER, 5);
    g_assert_cmpint(token->get_type(token), ==, NUMBER);
    g_assert_cmpint(token->get_payload(token), ==, 5);
    Token_destroy(token);
}
