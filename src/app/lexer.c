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

#include <string.h>

#include "core/bool.h"
#include "lexer.h"

static Token lexer_lang_token(Lexer*, Status*);
static Token lexer_number_token(Lexer*);
static Token lexer_base_token(Lexer*, Status*);

static void lexer_skip_spaces(Lexer*);
static void lexer_advance(Lexer*);

static bool lexer_at_end(const Lexer*);
static bool lexer_is_space(const Lexer*);
static bool lexer_is_digit(const Lexer*);

extern void lexer_init(Lexer* lexer, const char* expression) {
    lexer->current = expression[0];
    lexer->expression = (String) { strlen(expression), expression };
    lexer->position = 0;
}

extern Token lexer_next(Lexer* lexer, Status* status) {
    while (lexer && !lexer_at_end(lexer)) {
        if (lexer_is_space(lexer)) {
            lexer_skip_spaces(lexer);
            continue;
        }
        return lexer_lang_token(lexer, status);
    }
    return (Token) { TOKEN_END };
}

static Token lexer_lang_token(Lexer* lexer, Status* status) {
    return lexer_is_digit(lexer)
        ? lexer_number_token(lexer)
        : lexer_base_token(lexer, status);
}

static Token lexer_number_token(Lexer* lexer) {
    double result = 0;
    while (!lexer_at_end(lexer) && lexer_is_digit(lexer)) {
        result *= 10;
        result += lexer->current - '0';
        lexer_advance(lexer);
    }
    return (Token) { TOKEN_NUMBER, result };
}

static Token lexer_base_token(Lexer* lexer, Status* status) {
    char current = lexer->current;
    lexer_advance(lexer);
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

static void lexer_skip_spaces(Lexer* lexer) {
    while (!lexer_at_end(lexer) && lexer_is_space(lexer)) {
        lexer_advance(lexer);
    }
}

static void lexer_advance(Lexer* lexer) {
    lexer->current = lexer->expression.content[++lexer->position];
}

static bool lexer_at_end(const Lexer* lexer) {
    return lexer->position >= lexer->expression.size;
}

static bool lexer_is_space(const Lexer* lexer) {
    return lexer->current == ' ';
}

static bool lexer_is_digit(const Lexer* lexer) {
    return lexer->current > 47 && lexer->current < 58;
}
