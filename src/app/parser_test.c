/* Parser test - Tests for math expression syntax analyzer
 * Copyright (C) 2020 Stan Vlad <vstan02@protonmail.com>
 *
 * This file is part of xCalc.
 *
 * xCalc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

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
