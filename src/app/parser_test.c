#include <glib.h>

#include "app_tests.h"
#include "parser.h"

static void test_parser_parser(void);
static void test_parser_parse(void);

void test_parser(void) {
    g_test_add_func(TEST_PARSER_PATH "/parser", test_parser_parser);
    g_test_add_func(TEST_PARSER_PATH "/process", test_parser_parse);
}

static void test_parser_parser(void) {
    Parser* parser = parser_create("4 + 7");
    g_assert_nonnull(parser);
    parser_destroy(parser);
}

static void verify_expression_processing(const char* exp, double result) {
    Parser* parser = parser_create(exp);
    Status status = STATUS_SUCCESS;
    double res = parser_parse(parser, &status);
    g_assert_cmpint(status, ==, STATUS_SUCCESS);
    g_assert_cmpfloat(res, ==, result);
    parser_destroy(parser);
}

static void test_parser_parse(void) {
    verify_expression_processing("3", 3);
    verify_expression_processing("3 + 4 * 2", 11);
    verify_expression_processing("2 * (3 + 4)", 14);
}
