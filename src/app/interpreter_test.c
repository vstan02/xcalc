#include <gtk/gtk.h>

#include "core/test.h"
#include "interpreter.h"

static void test_interpreter_main(void);

void test_interpreter(void) {
    test_interpreter_main();
}

static void test_interpreter_main(void) {
    Interpreter* interpreter = Interpreter_create(Expression_create("4 + 7"));
    g_assert_nonnull(interpreter);
    Interpreter_destroy(interpreter);
}
