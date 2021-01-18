#include <glib.h>

#include "app_tests.h"
#include "lexer.h"

static void test_lexer_lexer(void);
static void test_lexer_get_next_token(void);

void test_lexer(void) {
    g_test_add_func(TEST_LEXER_PATH "/lexer", test_lexer_lexer);
    g_test_add_func(TEST_LEXER_PATH "/get_next_token", test_lexer_get_next_token);
}

static void test_lexer_lexer(void) {
    Lexer* lexer = lexer_create("test");
    g_assert_nonnull(lexer);
    lexer_destroy(lexer);
}

static void verify_next_token_type(Lexer* lexer, TokenType type) {
    Status status = STATUS_SUCCESS;
    Token* token = lexer_get_next(lexer, &status);
    g_assert_cmpint(status, ==, STATUS_SUCCESS);
    g_assert_cmpint(token_get_type(token), ==, type);
}

static void test_lexer_get_next_token(void) {
    Lexer* lexer = lexer_create("3 * (+2)");
    verify_next_token_type(lexer, TOKEN_NUMBER);
    verify_next_token_type(lexer, TOKEN_STAR);
    verify_next_token_type(lexer, TOKEN_LPAREN);
    verify_next_token_type(lexer, TOKEN_PLUS);
    verify_next_token_type(lexer, TOKEN_NUMBER);
    verify_next_token_type(lexer, TOKEN_RPAREN);
    verify_next_token_type(lexer, TOKEN_END);
    lexer_destroy(lexer);
}
