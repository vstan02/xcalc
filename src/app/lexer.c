/**
 * xCalc - A fast and simple to use calculator
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

#include <malloc.h>
#include <stdbool.h>

#include "core/error.h"
#include "expression.h"
#include "lexer.h"

#define PRIVATE(object) ((PRIVATE_DATA*) MODULE_PRIVATE(lexer, object))

PRIVATE_DATA {
    char current;
    Expression* expression;
    size_t position;
};

static char lexer_get_current(Lexer* self) {
    return PRIVATE(self)->current;
}

static Expression* lexer_get_expression(Lexer* self) {
    return PRIVATE(self)->expression;
}

static size_t lexer_get_position(Lexer* self) {
    return PRIVATE(self)->position;
}

static char lexer_get_next_char(Lexer* self) {
    Expression* expression = lexer_get_expression(self);
    return expression_get_char(expression, lexer_get_position(self));
}

static bool lexer_is_parenthesis(Lexer* self) {
    return lexer_get_current(self) == '(' || lexer_get_current(self) == ')';
}

static bool lexer_is_digit(Lexer* self) {
    return lexer_get_current(self) > 47 && lexer_get_current(self) < 58;
}

static bool lexer_is_ignorable_char(Lexer* self) {
    return lexer_get_current(self) == ' ';
}

static bool lexer_is_valid_position(Lexer* self) {
    Expression* expression = lexer_get_expression(self);
    return lexer_get_position(self) < expression_get_size(expression);
}

static void lexer_advance(Lexer* self) {
    ++PRIVATE(self)->position;
    PRIVATE(self)->current = lexer_get_next_char(self);
}

static void lexer_skip_ignorable_char(Lexer* self) {
    while (lexer_is_valid_position(self) && lexer_is_ignorable_char(self)) {
        lexer_advance(self);
    }
}

static Token* lexer_get_next_number_token(Lexer* self) {
    double result = 0;
    while (lexer_is_valid_position(self) && lexer_is_digit(self)) {
        result *= 10;
        result += lexer_get_current(self) - '0';
        lexer_advance(self);
    }
    return token_create(NUMBER, result);
}

static Token* lexer_get_next_paren_token(Lexer* self) {
    switch (lexer_get_current(self)) {
        case '(':
            lexer_advance(self);
            return token_create(LPAREN, 0);
        case ')':
            lexer_advance(self);
            return token_create(RPAREN, 0);
        default:
            throw_error("Lexer::get_next_paren_token - Invalid parenthesis");
    }
}

static Token* lexer_get_next_operator_token(Lexer* self) {
    switch (lexer_get_current(self)) {
        case '+':
            lexer_advance(self);
            return token_create(PLUS, 0);
        case '-':
            lexer_advance(self);
            return token_create(MINUS, 0);
        case '*':
            lexer_advance(self);
            return token_create(MULTIPLICATION, 0);
        case '/':
            lexer_advance(self);
            return token_create(DIVISION, 0);
        default:
            throw_error("Lexer::get_next_operator_token - Invalid operator");
    }
}

static Token* lexer_get_next_lang_token(Lexer* self) {
    if (lexer_is_digit(self)) {
        return lexer_get_next_number_token(self);
    }

    if (lexer_is_parenthesis(self)) {
        return lexer_get_next_paren_token(self);
    }

    return lexer_get_next_operator_token(self);
}

Token* lexer_get_next_token(Lexer* self) {
    while (lexer_is_valid_position(self)) {
        if (lexer_is_ignorable_char(self)) {
            lexer_skip_ignorable_char(self);
            continue;
        }
        return lexer_get_next_lang_token(self);
    }
    return token_create(END, 0);
}

MODULE_SET_CONSTRUCTOR(
    lexer, Lexer,
    MODULE_INIT_PARAMS(expression),
    char* expression
) {
    MODULE_INIT_PRIVATE(lexer, self);
    PRIVATE(self)->position = 0;
    PRIVATE(self)->expression = expression_create(expression);
    PRIVATE(self)->current = expression[0];
}

MODULE_SET_DESTRUCTOR(lexer, Lexer) {
    expression_destroy(PRIVATE(self)->expression);
    free(PRIVATE(self));
}
