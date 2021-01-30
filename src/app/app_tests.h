/* App tests - Tests for App module
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

#ifndef XCALC_APP_TESTS_H
#define XCALC_APP_TESTS_H

#define TEST_TOKEN_PATH "/app/token"
#define TEST_TEXT_PATH "/app/text"
#define TEST_LEXER_PATH "/app/lexer"
#define TEST_PARSER_PATH "/app/parser"

void test_token(void);
void test_text(void);
void test_lexer(void);
void test_parser(void);

#endif // XCALC_APP_TESTS_H
