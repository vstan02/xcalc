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

#include <stdbool.h>

#include "parser.h"

static double parse_expr(Parser*, Status*);
static double parse_term(Parser*, Status*);
static double parse_factor(Parser*, Status*);
static double parse_paren(Parser*, Status*);

static void consume(Parser*, TokenType, Status*);

static inline void advance(Parser* parser, Status* status) {
    parser->token = lexer_next(&parser->lexer, status);
}

static inline bool check(Parser* parser, TokenType type) {
    return parser->token.type == type;
}

static inline bool match(Parser* parser, TokenType type1, TokenType type2) {
    return check(parser, type1) || check(parser, type2);
}

/* Grammar:
 * > expr: term (PLUS|MINUS term)*
 * > term: factor (STAR|SLASH factor)*
 * > factor: NUMBER | -factor | paren
 * > paren: LPAREN expr RPAREN
 */
extern void parser_init(Parser* parser, const char* expression) {
    parser->status = STATUS_SUCCESS;
    lexer_init(&parser->lexer, expression);
    parser->token = lexer_next(&parser->lexer, &parser->status);
}

extern double parser_parse(Parser* parser, Status* status) {
    if (parser && parser->status == STATUS_SUCCESS)
        return parse_expr(parser, status);
    *status = parser->status;
    return 0;
}

static double parse_expr(Parser* parser, Status* status) {
    double result = parse_term(parser, status);
    while (match(parser, TOKEN_PLUS, TOKEN_MINUS)) {
        Token token = parser->token;
        advance(parser, status);
        result = token.type == TOKEN_PLUS
            ? result + parse_term(parser, status)
            : result - parse_term(parser, status);
    }
    return result;
}

static double parse_term(Parser* parser, Status* status) {
    double result = parse_factor(parser, status);
    while (match(parser, TOKEN_STAR, TOKEN_SLASH)) {
        Token token = parser->token;
        advance(parser, status);
        result = token.type == TOKEN_STAR
            ? result * parse_factor(parser, status)
            : result / parse_factor(parser, status);
    }
    return result;
}

static double parse_factor(Parser* parser, Status* status) {
    Token token = parser->token;
    switch (token.type) {
        case TOKEN_NUMBER:
            advance(parser, status);
            return token.value;
        case TOKEN_MINUS:
            advance(parser, status);
            return -parse_factor(parser, status);
        default:
            return parse_paren(parser, status);
    }
}

static double parse_paren(Parser* parser, Status* status) {
    consume(parser, TOKEN_LPAREN, status);
    double result = parse_expr(parser, status);
    consume(parser, TOKEN_RPAREN, status);
    return result;
}

static void consume(Parser* parser, TokenType type, Status* status) {
    if (check(parser, type)) {
        advance(parser, status);
    } else {
        *status = STATUS_INVARG;
    }
}
