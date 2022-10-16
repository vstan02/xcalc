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
static token_t id_token(lexer_t*);
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
    return lexer->current >= '0' && lexer->current <= '9';
}

static inline bool is_alpha(const lexer_t* lexer) {
    return lexer->current == '_'
        || lexer->current >= 'a' && lexer->current <= 'z'
        || lexer->current >= 'A' && lexer->current <= 'Z';
}

static inline bool is_alphanum(const lexer_t* lexer) {
    return is_digit(lexer) || is_alpha(lexer);
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
    if (is_alpha(lexer)) {
        return id_token(lexer);
    }
    return is_digit(lexer)
        ? number_token(lexer)
        : base_token(lexer, status);
}

static token_t number_token(lexer_t* lexer) {
    size_t start = lexer->position;
    while (!at_end(lexer) && is_digit(lexer)) {
        advance(lexer);
    }
    if (lexer->current == '.') {
        advance(lexer);
        while (!at_end(lexer) && is_digit(lexer)) {
            advance(lexer);
        }
    }
    return (token_t) {
        .type = TOKEN_NUMBER,
        .value = {
            .content = lexer->expression.content + start,
            .size = lexer->position - start
        }
    };
}

static token_t id_token(lexer_t* lexer) {
    size_t start = lexer->position;
    while (!at_end(lexer) && is_alphanum(lexer)) {
        advance(lexer);
    }
    return (token_t) {
        .type = TOKEN_ID,
        .value = {
            .content = lexer->expression.content + start,
            .size = lexer->position - start
        }
    };
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
        case '$': return (token_t) { TOKEN_DOLLAR };
        case '=': return (token_t) { TOKEN_EQUAL };
        default: *status = STATUS_INVARG;
    }
    return (token_t) { TOKEN_END };
}

static void skip_spaces(lexer_t* lexer) {
    while (!at_end(lexer) && is_space(lexer)) {
        advance(lexer);
    }
}
