/* xCalc - A fast and simple to use calculator
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

#include "core/private.h"
#include "text.h"
#include "lexer.h"

PRIVATE_DATA {
    char current;
    Text* expression;
    int8_t position;
};

static bool lexer_is_valid_position(Lexer* self) {
    return PRIVATE(self)->position < text_get_size(PRIVATE(self)->expression);
}

static bool lexer_is_space(Lexer* self) {
    return PRIVATE(self)->current == ' ';
}

static bool lexer_is_digit(Lexer* self) {
    return PRIVATE(self)->current > 47 || PRIVATE(self)->current < 58;
}

static bool lexer_is_parenthesis(Lexer* self) {
    return PRIVATE(self)->current == '(' || PRIVATE(self)->current == ')';
}

static bool lexer_is_operator(Lexer* self) {
    char current = PRIVATE(self)->current;
    return current == '+' || current == '-' || current == '*' || current == '/';
}

static void lexer_advance(Lexer* self) {
    PRIVATE(self)->current = text_get_char(
        PRIVATE(self)->expression,
        ++PRIVATE(self)->position
    );
}

static void lexer_skip_spaces(Lexer* self) {
    while (lexer_is_valid_position(self) && lexer_is_space(self)) {
        lexer_advance(self);
    }
}

static Token* lexer_get_next_paren(Lexer* self) {
    char current = PRIVATE(self)->current;
    lexer_advance(self);
    return current == '('
        ? token_create(LPAREN, 0)
        : token_create(RPAREN, 0);
}

static Token* lexer_get_next_number(Lexer* self) {
    double result = 0;
    while (lexer_is_valid_position(self) && lexer_is_digit(self)) {
        result *= 10;
        result += PRIVATE(self)->current - '0';
        lexer_advance(self);
    }
    return token_create(NUMBER, result);
}

static Token* lexer_get_next_operator(Lexer* self) {
    char current = PRIVATE(self)->current;
    lexer_advance(self);
    switch (current) {
        case '+': return token_create(PLUS, 0);
        case '-': return token_create(MINUS, 0);
        case '*': return token_create(MULTIPLICATION, 0);
        case '/': return token_create(DIVISION, 0);
        default: return NULL;
    }
}

static Token* lexer_process_lang(Lexer* self, int8_t* error) {
    if (lexer_is_digit(self))
        return lexer_get_next_number(self);
    if (lexer_is_parenthesis(self))
        return lexer_get_next_paren(self);
    if (lexer_is_operator(self))
        return lexer_get_next_operator(self);
    *error = 22;
    return NULL;
}

static Token* lexer_get_next(Lexer* self, int8_t* error) {
    while (lexer_is_valid_position(self)) {
        if (lexer_is_space(self)) {
            lexer_skip_spaces(self);
            continue;
        }
        return lexer_process_lang(self, error);
    }
    return token_create(END, 0);
}

void lexer_init(Lexer* self, const char* expression) {
    PRIVATE_INIT(self);
    PRIVATE(self)->current = expression[0];
    PRIVATE(self)->expression = text_create(expression);
    PRIVATE(self)->position = 0;
}

Lexer* lexer_create(const char* expression) {
    Lexer* self = (Lexer*) malloc(sizeof(Lexer));
    lexer_init(self, expression);
    return self;
}

void lexer_reset(Lexer* self) {
    text_destroy(PRIVATE(self)->expression);
    PRIVATE_RESET(self);
}

void lexer_destroy(Lexer* self) {
    if (self) {
        lexer_reset(self);
        free(self);
    }
}
