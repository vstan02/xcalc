/* Token test - Tests for math expression tokens
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
#include "token.h"

static void test_token_token(void);
static void test_token_getters(void);

void test_token(void) {
    g_test_add_func(TEST_TOKEN_PATH "/token", test_token_token);
    g_test_add_func(TEST_TOKEN_PATH "/getters", test_token_getters);
}

static void test_token_token(void) {
    Token* token = token_create(TOKEN_NUMBER, 5);
    g_assert_nonnull(token);
    token_destroy(token);
}

static void test_token_getters(void) {
    Token* token = token_create(TOKEN_NUMBER, 5);
    g_assert_cmpint(token_get_type(token), ==, TOKEN_NUMBER);
    g_assert_cmpint(token_get_payload(token), ==, 5);
    token_destroy(token);
}
