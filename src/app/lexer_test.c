#include <gtk/gtk.h>

#include "core/test.h"
#include "lexer.h"

static void test_lexer_main(void);
static void test_lexer_get_next_token(void);

void test_lexer(void) {
    test_lexer_main();
    g_test_add_func(TEST_LEXER_PATH "/get_next_token", test_lexer_get_next_token);
}

static void test_lexer_main(void) {
    Lexer* lexer = Lexer_create(Expression_create("test"));
    g_assert_nonnull(lexer);
    Lexer_destroy(lexer);
}

static void verify_next_token_type(Lexer* lexer, TokenType type) {
    Token* token = lexer->get_next_token(lexer);
    g_assert_cmpint(token->get_type(token), ==, type);
}

static void test_lexer_get_next_token(void) {
    Lexer* lexer = Lexer_create(Expression_create("3 * (+2)"));
    verify_next_token_type(lexer, NUMBER);
    verify_next_token_type(lexer, MULTIPLICATION);
    verify_next_token_type(lexer, LPAREN);
    verify_next_token_type(lexer, PLUS);
    verify_next_token_type(lexer, NUMBER);
    verify_next_token_type(lexer, RPAREN);
    verify_next_token_type(lexer, END);
    Lexer_destroy(lexer);
}
