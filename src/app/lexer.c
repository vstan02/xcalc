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
#include "lexer.h"

#define PRIVATE(object) ((PRIVATE_DATA*) MODULE_PRIVATE(Lexer, object))

PRIVATE_DATA {
    char current;
    Expression* expression;
    size_t position;
};

static char get_current(Lexer* self) {
    return PRIVATE(self)->current;
}

static Expression* get_expression(Lexer* self) {
    return PRIVATE(self)->expression;
}

static size_t get_position(Lexer* self) {
    return PRIVATE(self)->position;
}

static char get_next_char(Lexer* self) {
    Expression* expression = get_expression(self);
    return expression->get_char(expression, get_position(self));
}

static bool is_parenthesis(Lexer* self) {
    return get_current(self) == '(' || get_current(self) == ')';
}

static bool is_digit(Lexer* self) {
    return get_current(self) > 47 && get_current(self) < 58;
}

static bool is_ignorable_char(Lexer* self) {
    return get_current(self) == ' ';
}

static bool is_valid_position(Lexer* self) {
    Expression* expression = get_expression(self);
    return get_position(self) < expression->get_size(expression);
}

static void advance(Lexer* self) {
    ++PRIVATE(self)->position;
    PRIVATE(self)->current = get_next_char(self);
}

static void skip_ignorable_char(Lexer* self) {
    while (is_valid_position(self) && is_ignorable_char(self)) {
        advance(self);
    }
}

static Token* get_next_number_token(Lexer* self) {
    double result = 0;
    while (is_valid_position(self) && is_digit(self)) {
        result *= 10;
        result += get_current(self) - '0';
        advance(self);
    }
    return Token_create(NUMBER, result);
}

static Token* get_next_paren_token(Lexer* self) {
    switch (get_current(self)) {
        case '(':
            advance(self);
            return Token_create(LPAREN, 0);
        case ')':
            advance(self);
            return Token_create(RPAREN, 0);
        default:
            throw_error("Lexer::get_next_paren_token - Invalid parenthesis");
    }
}

static Token* get_next_operator_token(Lexer* self) {
    switch (get_current(self)) {
        case '+':
            advance(self);
            return Token_create(PLUS, 0);
        case '-':
            advance(self);
            return Token_create(MINUS, 0);
        case '*':
            advance(self);
            return Token_create(MULTIPLICATION, 0);
        case '/':
            advance(self);
            return Token_create(DIVISION, 0);
        default:
            throw_error("Lexer::get_next_operator_token - Invalid operator");
    }
}

static Token* get_next_lang_token(Lexer* self) {
    if (is_digit(self)) {
        return get_next_number_token(self);
    }

    if (is_parenthesis(self)) {
        return get_next_paren_token(self);
    }

    return get_next_operator_token(self);
}

static Token* get_next_token(Lexer* self) {
    while (is_valid_position(self)) {
        if (is_ignorable_char(self)) {
            skip_ignorable_char(self);
            continue;
        }
        return get_next_lang_token(self);
    }
    return Token_create(END, 0);
}

MODULE_SET_CONSTRUCTOR(Lexer, MODULE_INIT_PARAMS(expression), Expression* expression) {
    MODULE_INIT_PRIVATE(Lexer, self);

    PRIVATE(self)->position = 0;
    PRIVATE(self)->expression = expression;
    PRIVATE(self)->current = expression->get_char(expression, 0);

    self->get_next_token = get_next_token;
}

MODULE_SET_DESTRUCTOR(Lexer) {
    free(PRIVATE(self)->expression);
    free(PRIVATE(self));
}
