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

#include "tests/app_tests.h"
#include "parser.h"

static void test_parser_parse(void);

extern void add_parser_tests(void) {
    g_test_add_func(TEST_PARSER_PATH "/process", test_parser_parse);
}

static void verify_expression_processing(const char* expression, double expected) {
    Parser parser;
    parser_init(&parser, expression);
    Status status = STATUS_SUCCESS;
    double result = parser_parse(&parser, &status);
    g_assert_cmpint(status, ==, STATUS_SUCCESS);
    g_assert_cmpfloat(result, ==, expected);
}

static void test_parser_parse(void) {
    verify_expression_processing("3", 3);
    verify_expression_processing("3 + 4 * 2", 11);
    verify_expression_processing("2 * (3 + 4)", 14);
}
