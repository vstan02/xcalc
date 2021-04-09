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

#include "core/bool.h"
#include "parser.h"

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
extern void parser_init(Parser* parser, const char* expression) {
    parser->status = STATUS_SUCCESS;
    lexer_init(&parser->lexer, expression);
    parser->token = lexer_next(&parser->lexer, &parser->status);
}

extern double parser_parse(Parser* parser, Status* status) {
    if (parser && parser->status == STATUS_SUCCESS)
        return parser_parse_expr(parser, status);
    *status = parser->status;
    return 0;
}

static double parser_parse_expr(Parser* parser, Status* status) {
    double result = parser_parse_term(parser, status);
    while (parser_match(parser, TOKEN_PLUS, TOKEN_MINUS)) {
        Token token = parser->token;
        parser_advance(parser, status);
        result = token.type == TOKEN_PLUS
            ? result + parser_parse_term(parser, status)
            : result - parser_parse_term(parser, status);
    }
    return result;
}

static double parser_parse_term(Parser* parser, Status* status) {
    double result = parser_parse_factor(parser, status);
    while (parser_match(parser, TOKEN_STAR, TOKEN_SLASH)) {
        Token token = parser->token;
        parser_advance(parser, status);
        result = token.type == TOKEN_STAR
            ? result * parser_parse_factor(parser, status)
            : result / parser_parse_factor(parser, status);
    }
    return result;
}

static double parser_parse_factor(Parser* parser, Status* status) {
    Token token = parser->token;
    switch (token.type) {
        case TOKEN_NUMBER:
            parser_advance(parser, status);
            return token.value;
        case TOKEN_MINUS:
            parser_advance(parser, status);
            return -parser_parse_factor(parser, status);
        default:
            return parser_parse_paren(parser, status);
    }
}

static double parser_parse_paren(Parser* parser, Status* status) {
    parser_consume(parser, TOKEN_LPAREN, status);
    double result = parser_parse_expr(parser, status);
    parser_consume(parser, TOKEN_RPAREN, status);
    return result;
}

static void parser_consume(Parser* parser, TokenType type, Status* status) {
    if (parser_check(parser, type)) {
        parser_advance(parser, status);
    } else {
        *status = STATUS_INVARG;
    }
}

static void parser_advance(Parser* parser, Status* status) {
    parser->token = lexer_next(&parser->lexer, status);
}

static bool parser_match(Parser* parser, TokenType type1, TokenType type2) {
    return parser_check(parser, type1) || parser_check(parser, type2);
}

static bool parser_check(Parser* parser, TokenType type) {
    return parser->token.type == type;
}
