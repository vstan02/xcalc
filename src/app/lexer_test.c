#include <gtk/gtk.h>

#include "core/test.h"
#include "lexer.h"

static void test_lexer_main(void);

void test_lexer(void) {
    test_lexer_main();
}

static void test_lexer_main(void) {
    Lexer* lexer = Lexer_create(Expression_create("test"));
    g_assert_nonnull(lexer);
    Lexer_destroy(lexer);
}
