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

static token_t lang_token(lexer_t*, status_t*);
static token_t number_token(lexer_t*);
static token_t base_token(lexer_t*, status_t*);

static void skip_spaces(lexer_t*);

static inline void advance(lexer_t* lexer) {
    lexer->current = lexer->expression.content[++lexer->position];
}

static inline bool at_end(const lexer_t* lexer) {
    return lexer->position >= lexer->expression.size;
}

static inline bool is_space(const lexer_t* lexer) {
    return lexer->current == ' ';
}

static inline bool is_digit(const lexer_t* lexer) {
    return lexer->current > 47 && lexer->current < 58;
}

extern void lexer_init(lexer_t* lexer, const char* expression) {
    lexer->current = expression[0];
    lexer->expression = (string_t) { strlen(expression), expression };
    lexer->position = 0;
}

extern token_t lexer_next(lexer_t* lexer, status_t* status) {
    while (lexer && !at_end(lexer)) {
        if (is_space(lexer)) {
            skip_spaces(lexer);
            continue;
        }
        return lang_token(lexer, status);
    }
    return (token_t) { TOKEN_END };
}

static token_t lang_token(lexer_t* lexer, status_t* status) {
    return is_digit(lexer)
        ? number_token(lexer)
        : base_token(lexer, status);
}

static token_t number_token(lexer_t* lexer) {
    double result = 0;
    while (!at_end(lexer) && is_digit(lexer)) {
        result *= 10;
        result += lexer->current - '0';
        advance(lexer);
    }
    return (token_t) { TOKEN_NUMBER, result };
}

static token_t base_token(lexer_t* lexer, status_t* status) {
    char current = lexer->current;
    advance(lexer);
    switch (current) {
        case '+': return (token_t) { TOKEN_PLUS };
        case '-': return (token_t) { TOKEN_MINUS };
        case '*': return (token_t) { TOKEN_STAR };
        case '/': return (token_t) { TOKEN_SLASH };
        case '(': return (token_t) { TOKEN_LPAREN };
        case ')': return (token_t) { TOKEN_RPAREN };
        default: *status = STATUS_INVARG;
    }
    return (token_t) { TOKEN_END };
}

static void skip_spaces(lexer_t* lexer) {
    while (!at_end(lexer) && is_space(lexer)) {
        advance(lexer);
    }
}
