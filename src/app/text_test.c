/* Text test - Tests for string work routines
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
#include "text.h"

static void test_text_text(void);
static void test_text_getters(void);

void test_text(void) {
    g_test_add_func(TEST_TEXT_PATH "/text", test_text_text);
    g_test_add_func(TEST_TEXT_PATH "/getters", test_text_getters);
}

static void test_text_text(void) {
    Text* text = text_create("test");
    g_assert_nonnull(text);
    text_destroy(text);
}

static void test_text_getters(void) {
    Text* text = text_create("test");
    g_assert_cmpint((uint8_t) text_get_size(text), ==, 4);
    g_assert_cmpint((uint8_t) text_get_char(text, 1), ==, 'e');
    text_destroy(text);
}
