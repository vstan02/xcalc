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
#include <stdlib.h>
#include <string.h>

#include "parser.h"

static double parse_decl(parser_t*, status_t*);
static double parse_call(parser_t*, status_t*);
static double parse_expr(parser_t*, status_t*);
static double parse_term(parser_t*, status_t*);
static double parse_factor(parser_t*, status_t*);
static double parse_paren(parser_t*, status_t*);

static void consume(parser_t*, token_type_t, status_t*);

static inline void advance(parser_t* parser, status_t* status) {
    parser->token = lexer_next(&parser->lexer, status);
}

static inline bool check(parser_t* parser, token_type_t type) {
    return parser->token.type == type;
}

static inline bool match(parser_t* parser, token_type_t type1, token_type_t type2) {
    return check(parser, type1) || check(parser, type2);
}

/* Grammar:
 * > var_decl: DOLLAR ID EQUAL expr
 * > expr: term (PLUS|MINUS term)*
 * > term: factor (STAR|SLASH factor)*
 * > factor: NUMBER | ID | -factor | paren
 * > paren: LPAREN expr RPAREN
 */
extern void parser_init(parser_t* parser, vars_t* vars, const char* expression) {
    parser->status = STATUS_SUCCESS;
    parser->vars = vars;
    lexer_init(&parser->lexer, expression);
    parser->token = lexer_next(&parser->lexer, &parser->status);
}

extern double parser_parse(parser_t* parser, status_t* status) {
    if (!parser || !parser->status == STATUS_SUCCESS) {
        *status = parser->status;
        return 0;
    }

    return parser->token.type == TOKEN_DOLLAR
        ? parse_decl(parser, status)
        : parse_expr(parser, status);
}

static double parse_expr(parser_t* parser, status_t* status) {
    double result = parse_term(parser, status);
    while (match(parser, TOKEN_PLUS, TOKEN_MINUS)) {
        token_t token = parser->token;
        advance(parser, status);
        result = token.type == TOKEN_PLUS
            ? result + parse_term(parser, status)
            : result - parse_term(parser, status);
    }
    return result;
}

static double parse_term(parser_t* parser, status_t* status) {
    double result = parse_factor(parser, status);
    while (match(parser, TOKEN_STAR, TOKEN_SLASH)) {
        token_t token = parser->token;
        advance(parser, status);
        result = token.type == TOKEN_STAR
            ? result * parse_factor(parser, status)
            : result / parse_factor(parser, status);
    }
    return result;
}

static double parse_factor(parser_t* parser, status_t* status) {
    token_t token = parser->token;
    switch (token.type) {
        case TOKEN_NUMBER:
            advance(parser, status);
            return strtod(token.value.content, NULL);
        case TOKEN_MINUS:
            advance(parser, status);
            return -parse_factor(parser, status);
        case TOKEN_PLUS:
            advance(parser, status);
            return parse_factor(parser, status);
        case TOKEN_ID:
            return parse_call(parser, status);
        case TOKEN_LPAREN:
            return parse_paren(parser, status);
        default:
            *status = STATUS_INVARG;
            return 0;
    }
}

static double parse_paren(parser_t* parser, status_t* status) {
    consume(parser, TOKEN_LPAREN, status);
    double result = parse_expr(parser, status);
    consume(parser, TOKEN_RPAREN, status);
    return result;
}

static double parse_decl(parser_t* parser, status_t* status) {
    consume(parser, TOKEN_DOLLAR, status);
    string_t id = parser->token.value;
    consume(parser, TOKEN_ID, status);
    consume(parser, TOKEN_EQUAL, status);
    char* name = strndup(id.content, id.size);
    double value = parse_expr(parser, status);

    vars_set(parser->vars, name, value);

    free(name);
    return value;
}

static double parse_call(parser_t* parser, status_t* status) {
    string_t id = parser->token.value;
    consume(parser, TOKEN_ID, status);

    char* name = strndup(id.content, id.size);
    double* value = vars_get(parser->vars, name);
    free(name);

    if (value != NULL) {
        return *value;
    }

    *status = STATUS_INVARG;
    return 0;
}

static void consume(parser_t* parser, token_type_t type, status_t* status) {
    if (check(parser, type)) {
        advance(parser, status);
    } else {
        *status = STATUS_INVARG;
    }
}
