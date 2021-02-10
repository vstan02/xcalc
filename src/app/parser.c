/* Parser - Math expression syntax analyzer
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

#include "core/bool.h"
#include "parser.h"
#include "lexer.h"

struct t_Parser {
    Lexer* lexer;
    Status status;
    Token token;
};

static double parser_parse_expr(Parser*, Status*);
static double parser_parse_term(Parser*, Status*);
static double parser_parse_factor(Parser*, Status*);
static double parser_parse_paren(Parser*, Status*);

static void parser_consume(Parser*, TokenType, Status*);
static void parser_advance(Parser*, Status*);

static bool parser_check(Parser*, TokenType);
static bool parser_match(Parser*, TokenType, TokenType);

/* Grammar:
 * > expr: term (PLUS|MINUS term)*
 * > term: factor (STAR|SLASH factor)*
 * > factor: NUMBER | -factor | paren
 * > paren: LPAREN expr RPAREN
 */
extern Parser* parser_create(const char* expression) {
    Parser* self = (Parser*) malloc(sizeof(Parser));
    self->status = STATUS_SUCCESS;
    self->lexer = lexer_create(expression);
    self->token = lexer_get_next(self->lexer, &self->status);
    return self;
}

extern void parser_destroy(Parser* self) {
    if (self) {
        lexer_destroy(self->lexer);
        free(self);
    }
}

extern double parser_parse(Parser* self, Status* status) {
    if (self && self->status == STATUS_SUCCESS)
        return parser_parse_expr(self, status);
    *status = self->status;
    return 0;
}

static double parser_parse_expr(Parser* self, Status* status) {
    double result = parser_parse_term(self, status);
    while (parser_match(self, TOKEN_PLUS, TOKEN_MINUS)) {
        Token token = self->token;
        parser_advance(self, status);
        result = token.type == TOKEN_PLUS
            ? result + parser_parse_term(self, status)
            : result - parser_parse_term(self, status);
    }
    return result;
}

static double parser_parse_term(Parser* self, Status* status) {
    double result = parser_parse_factor(self, status);
    while (parser_match(self, TOKEN_STAR, TOKEN_SLASH)) {
        Token token = self->token;
        parser_advance(self, status);
        result = token.type == TOKEN_STAR
            ? result * parser_parse_factor(self, status)
            : result / parser_parse_factor(self, status);
    }
    return result;
}

static double parser_parse_factor(Parser* self, Status* status) {
    Token token = self->token;
    switch (token.type) {
        case TOKEN_NUMBER:
            parser_advance(self, status);
            return token.value;
        case TOKEN_MINUS:
            parser_advance(self, status);
            return -parser_parse_factor(self, status);
        default:
            return parser_parse_paren(self, status);
    }
}

static double parser_parse_paren(Parser* self, Status* status) {
    parser_consume(self, TOKEN_LPAREN, status);
    double result = parser_parse_expr(self, status);
    parser_consume(self, TOKEN_RPAREN, status);
    return result;
}

static void parser_consume(Parser* self, TokenType type, Status* status) {
    if (parser_check(self, type)) {
        parser_advance(self, status);
    } else {
        *status = STATUS_INVARG;
    }
}

static void parser_advance(Parser* self, Status* status) {
    self->token = lexer_get_next(self->lexer, status);
}

static bool parser_match(Parser* self, TokenType type1, TokenType type2) {
    return parser_check(self, type1) || parser_check(self, type2);
}

static bool parser_check(Parser* self, TokenType type) {
    return self->token.type == type;
}
