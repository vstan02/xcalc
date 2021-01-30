/* Lexer - Math expression lexical analyzer
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
#include <inttypes.h>

#include "core/bool.h"
#include "text.h"
#include "lexer.h"

struct t_Lexer {
    char current;
    Text* expression;
    int8_t position;
};

static Token* lexer_get_lang_token(Lexer*, Status*);
static Token* lexer_get_number_token(Lexer*);
static Token* lexer_get_base_token(Lexer*, Status*);

static void lexer_skip_spaces(Lexer*);
static void lexer_advance(Lexer*);

static bool lexer_at_end(const Lexer*);
static bool lexer_is_space(const Lexer*);
static bool lexer_is_digit(const Lexer*);

extern Lexer* lexer_create(const char* expression) {
    Lexer* self = (Lexer*) malloc(sizeof(Lexer));
    self->current = expression[0];
    self->expression = text_create(expression);
    self->position = 0;
    return self;
}

extern void lexer_destroy(Lexer* self) {
    if (self) {
        text_destroy(self->expression);
        free(self);
    }
}

extern Token* lexer_get_next(Lexer* self, Status* status) {
    while (self && !lexer_at_end(self)) {
        if (lexer_is_space(self)) {
            lexer_skip_spaces(self);
            continue;
        }
        return lexer_get_lang_token(self, status);
    }
    return token_create(TOKEN_END, 0);
}

static Token* lexer_get_lang_token(Lexer* self, Status* status) {
    return lexer_is_digit(self)
        ? lexer_get_number_token(self)
        : lexer_get_base_token(self, status);
}

static Token* lexer_get_number_token(Lexer* self) {
    double result = 0;
    while (!lexer_at_end(self) && lexer_is_digit(self)) {
        result *= 10;
        result += self->current - '0';
        lexer_advance(self);
    }
    return token_create(TOKEN_NUMBER, result);
}

static Token* lexer_get_base_token(Lexer* self, Status* status) {
    char current = self->current;
    lexer_advance(self);
    switch (current) {
        case '+': return token_create(TOKEN_PLUS, 0);
        case '-': return token_create(TOKEN_MINUS, 0);
        case '*': return token_create(TOKEN_STAR, 0);
        case '/': return token_create(TOKEN_SLASH, 0);
        case '(': return token_create(TOKEN_LPAREN, 0);
        case ')': return token_create(TOKEN_RPAREN, 0);
        default: *status = STATUS_INVARG; return NULL;
    }
}

static void lexer_skip_spaces(Lexer* self) {
    while (!lexer_at_end(self) && lexer_is_space(self)) {
        lexer_advance(self);
    }
}

static void lexer_advance(Lexer* self) {
    self->current = text_get_char(self->expression, ++self->position);
}

static bool lexer_at_end(const Lexer* self) {
    return self->position >= text_get_size(self->expression);
}

static bool lexer_is_space(const Lexer* self) {
    return self->current == ' ';
}

static bool lexer_is_digit(const Lexer* self) {
    return self->current > 47 && self->current < 58;
}
