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
    double result;
    Calculator* calculator = calculator_create();
    calculator_calculate(calculator, "4", &result);
    g_assert_cmpfloat(result, ==, 4);
    calculator_calculate(calculator, "4 + 2 * 3", &result);
    g_assert_cmpfloat(result, ==, 10);
    calculator_calculate(calculator, "(4 + 2) * 3", &result);
    g_assert_cmpfloat(result, ==, 18);
    calculator_destroy(calculator);
}
