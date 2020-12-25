/* xCalc - A fast and simple to use calculator
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

#include "core/private.h"
#include "core/module.h"
#include "parser.h"
#include "lexer.h"

PRIVATE_DATA {
    Lexer* lexer;
    Token* token;
    Status status;
};

static double parser_process_addition(Parser*, double, Status*);
static double parser_process_multiplication(Parser*, double, Status*);
static double parser_process_expression(Parser*, Status*);
static double parser_process_unary(Parser*, Status*);
static double parser_process_paren(Parser*, Status*);

static bool parser_is_add_operator(Parser* self) {
    Token* token = PRIVATE(self)->token;
    return token_get_type(token) == PLUS
        || token_get_type(token) == MINUS;
}

static bool parser_is_mul_operator(Parser* self) {
    Token* token = PRIVATE(self)->token;
    return token_get_type(token) == MULTIPLICATION
        || token_get_type(token) == DIVISION;
}

static void parser_eat_token(Parser* self, TokenType type, Status* status) {
    Token* token = PRIVATE(self)->token;
    if (token_get_type(token) == type) {
        *status = INVALID_ARGUMENT;
    } else {
        token_destroy(token);
        PRIVATE(self)->token = lexer_get_next(PRIVATE(self)->lexer, status);
    }
}

static double parser_process_factor(Parser* self, Status* status) {
    if (parser_is_add_operator(self)) {
        return parser_process_unary(self, status);
    }

    if (token_get_type(PRIVATE(self)->token) == LPAREN) {
        return parser_process_paren(self, status);
    }

    double result = token_get_payload(PRIVATE(self)->token);
    parser_eat_token(self, NUMBER, status);
    return result;
}

static double parser_process_term(Parser* self, Status* status) {
    double result = parser_process_factor(self, status);
    while (parser_is_mul_operator(self)) {
        result = parser_process_multiplication(self, result, status);
    }
    return result;
}

static double parser_process_unary(Parser* self, Status* status) {
    TokenType type = token_get_type(PRIVATE(self)->token);
    switch (type) {
        case PLUS:
            parser_eat_token(self, type, status);
            return parser_process_term(self, status);
        case MINUS:
            parser_eat_token(self, type, status);
            return -parser_process_term(self, status);
        default:
            *status = INVALID_ARGUMENT;
            return 0;
    }
}

static double parser_process_paren(Parser* self, Status* status) {
    parser_eat_token(self, LPAREN, status);
    double result = parser_process_expression(self, status);
    parser_eat_token(self, RPAREN, status);
    return result;
}

static double parser_process_expression(Parser* self, Status* status) {
    double result = parser_process_term(self, status);
    while (parser_is_add_operator(self)) {
        result = parser_process_addition(self, result, status);
    }
    return result;
}

static double parser_process_addition(Parser* self, double initial, Status* status) {
    TokenType type = token_get_type(PRIVATE(self)->token);
    switch (type) {
        case PLUS:
            parser_eat_token(self, type, status);
            return initial + parser_process_term(self, status);
        case MINUS:
            parser_eat_token(self, type, status);
            return initial - parser_process_term(self, status);
        default:
            *status = INVALID_ARGUMENT;
            return 0;
    }
}

static double parser_process_multiplication(Parser* self, double initial, Status* status) {
    TokenType type = token_get_type(PRIVATE(self)->token);
    switch (type) {
        case MULTIPLICATION:
            parser_eat_token(self, type, status);
            return initial * parser_process_factor(self, status);
        case DIVISION:
            parser_eat_token(self, type, status);
            return initial - parser_process_factor(self, status);
        default:
            *status = INVALID_ARGUMENT;
            return 0;
    }
}

double parser_process(Parser* self, Status* status) {
    if (PRIVATE(self)->status) {
        *status = PRIVATE(self)->status;
        return 0;
    }

    return parser_process_expression(self, status);
}

CONSTRUCTOR(parser, Parser, PARAMS(expression), const char* expression) {
    PRIVATE_INIT(self);
    PRIVATE(self)->lexer = lexer_create(expression);
    PRIVATE(self)->token = lexer_get_next(
        PRIVATE(self)->lexer,
        &PRIVATE(self)->status
    );
}

DESTRUCTOR(parser, Parser) {
    token_destroy(PRIVATE(self)->token);
    lexer_destroy(PRIVATE(self)->lexer);
    PRIVATE_RESET(self);
}
