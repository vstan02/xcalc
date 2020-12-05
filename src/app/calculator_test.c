#include <gtk/gtk.h>

#include "core/test.h"
#include "calculator.h"

static void test_calculator_main(void);
static void test_calculator_calculate(void);

void test_calculator(void) {
    test_calculator_main();
    g_test_add_func(TEST_CALCULATOR_PATH "/calculate", test_calculator_calculate);
}

static void test_calculator_main(void) {
    Calculator* calculator = Calculator_create();
    g_assert_nonnull(calculator);
    Calculator_destroy(calculator);
}

static void test_calculator_calculate(void) {
    Calculator* calculator = Calculator_create();
    g_assert_cmpfloat(calculator->calculate(calculator, "4"), ==, 4);
    Calculator_destroy(calculator);
}
