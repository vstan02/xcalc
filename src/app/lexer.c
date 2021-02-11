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
#include <string.h>

#include "core/bool.h"
#include "lexer.h"

typedef struct t_String String;

struct t_String {
    size_t size;
    const char* content;
};

struct t_Lexer {
    char current;
    String expression;
    size_t position;
};

static Token lexer_get_lang_token(Lexer*, Status*);
static Token lexer_get_number_token(Lexer*);
static Token lexer_get_base_token(Lexer*, Status*);

static void lexer_skip_spaces(Lexer*);
static void lexer_advance(Lexer*);

static bool lexer_at_end(const Lexer*);
static bool lexer_is_space(const Lexer*);
static bool lexer_is_digit(const Lexer*);

extern Lexer* lexer_create(const char* expression) {
    Lexer* self = (Lexer*) malloc(sizeof(Lexer));
    self->current = expression[0];
    self->expression = (String) { strlen(expression), expression };
    self->position = 0;
    return self;
}

extern void lexer_destroy(Lexer* self) {
    if (self) free(self);
}

extern Token lexer_get_next(Lexer* self, Status* status) {
    while (self && !lexer_at_end(self)) {
        if (lexer_is_space(self)) {
            lexer_skip_spaces(self);
            continue;
        }
        return lexer_get_lang_token(self, status);
    }
    return (Token) { TOKEN_END };
}

static Token lexer_get_lang_token(Lexer* self, Status* status) {
    return lexer_is_digit(self)
        ? lexer_get_number_token(self)
        : lexer_get_base_token(self, status);
}

static Token lexer_get_number_token(Lexer* self) {
    double result = 0;
    while (!lexer_at_end(self) && lexer_is_digit(self)) {
        result *= 10;
        result += self->current - '0';
        lexer_advance(self);
    }
    return (Token) { TOKEN_NUMBER, result };
}

static Token lexer_get_base_token(Lexer* self, Status* status) {
    char current = self->current;
    lexer_advance(self);
    switch (current) {
        case '+': return (Token) { TOKEN_PLUS };
        case '-': return (Token) { TOKEN_MINUS };
        case '*': return (Token) { TOKEN_STAR };
        case '/': return (Token) { TOKEN_SLASH };
        case '(': return (Token) { TOKEN_LPAREN };
        case ')': return (Token) { TOKEN_RPAREN };
        default: *status = STATUS_INVARG;
    }
    return (Token) { TOKEN_END };
}

static void lexer_skip_spaces(Lexer* self) {
    while (!lexer_at_end(self) && lexer_is_space(self)) {
        lexer_advance(self);
    }
}

static void lexer_advance(Lexer* self) {
    self->current = self->expression.content[++self->position];
}

static bool lexer_at_end(const Lexer* self) {
    return self->position >= self->expression.size;
}

static bool lexer_is_space(const Lexer* self) {
    return self->current == ' ';
}

static bool lexer_is_digit(const Lexer* self) {
    return self->current > 47 && self->current < 58;
}
