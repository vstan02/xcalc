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
#include <stdbool.h>

#include "lexer.h"

static Token lang_token(Lexer*, Status*);
static Token number_token(Lexer*);
static Token base_token(Lexer*, Status*);

static void skip_spaces(Lexer*);

static inline void advance(Lexer* lexer) {
    lexer->current = lexer->expression.content[++lexer->position];
}

static inline bool at_end(const Lexer* lexer) {
    return lexer->position >= lexer->expression.size;
}

static inline bool is_space(const Lexer* lexer) {
    return lexer->current == ' ';
}

static inline bool is_digit(const Lexer* lexer) {
    return lexer->current > 47 && lexer->current < 58;
}

extern void lexer_init(Lexer* lexer, const char* expression) {
    lexer->current = expression[0];
    lexer->expression = (String) { strlen(expression), expression };
    lexer->position = 0;
}

extern Token lexer_next(Lexer* lexer, Status* status) {
    while (lexer && !at_end(lexer)) {
        if (is_space(lexer)) {
            skip_spaces(lexer);
            continue;
        }
        return lang_token(lexer, status);
    }
    return (Token) { TOKEN_END };
}

static Token lang_token(Lexer* lexer, Status* status) {
    return is_digit(lexer)
        ? number_token(lexer)
        : base_token(lexer, status);
}

static Token number_token(Lexer* lexer) {
    double result = 0;
    while (!at_end(lexer) && is_digit(lexer)) {
        result *= 10;
        result += lexer->current - '0';
        advance(lexer);
    }
    return (Token) { TOKEN_NUMBER, result };
}

static Token base_token(Lexer* lexer, Status* status) {
    char current = lexer->current;
    advance(lexer);
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

static void skip_spaces(Lexer* lexer) {
    while (!at_end(lexer) && is_space(lexer)) {
        advance(lexer);
    }
}
