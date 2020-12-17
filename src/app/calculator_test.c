#include <gtk/gtk.h>

#include "app_tests.h"
#include "calculator.h"

static void test_calculator_calculator(void);
static void test_calculator_calculate(void);

void test_calculator(void) {
    g_test_add_func(TEST_CALCULATOR_PATH "/calculator", test_calculator_calculator);
    g_test_add_func(TEST_CALCULATOR_PATH "/calculate", test_calculator_calculate);
}

static void test_calculator_calculator(void) {
    Calculator* calculator = calculator_create();
    g_assert_nonnull(calculator);
    calculator_destroy(calculator);
}

static void test_calculator_calculate(void) {
    Calculator* calculator = calculator_create();
    g_assert_cmpfloat(calculator_calculate(calculator, "4"), ==, 4);
    g_assert_cmpfloat(calculator_calculate(calculator, "4 + 2 * 3"), ==, 10);
    g_assert_cmpfloat(calculator_calculate(calculator, "(4 + 2) * 3"), ==, 18);
    calculator_destroy(calculator);
}
