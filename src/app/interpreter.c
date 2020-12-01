/**
 * xCalc - A fast and simple to use calculator
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
#include <stdbool.h>

#include "core/error.h"
#include "interpreter.h"

#define PRIVATE(object) ((PRIVATE_DATA*) MODULE_PRIVATE(Interpreter, object))

PRIVATE_DATA {
    Lexer* lexer;
    Token* token;
};

static double process_unary(Interpreter*);
static double process_paren(Interpreter*);
static double process_expression(Interpreter*);
static double process_addition(Interpreter*, double);
static double process_multiplication(Interpreter*, double);

static Token* get_next_token(Interpreter* self) {
    Lexer* lexer = PRIVATE(self)->lexer;
    return lexer->get_next_token(lexer);
}

static Token* get_token(Interpreter* self) {
    return PRIVATE(self)->token;
}

static bool is_addition_operator(Interpreter* self) {
    Token* token = get_token(self);
    return token->get_type(token) == PLUS
        || token->get_type(token) == MINUS;
}

static bool is_multiplication_operator(Interpreter* self) {
    Token* token = get_token(self);
    return token->get_type(token) == MULTIPLICATION
        || token->get_type(token) == DIVISION;
}

static void eat_token(Interpreter* self, TokenType type) {
    Token *token = get_token(self);
    if (token->get_type(token) == type) {
        Token_destroy(token);
        PRIVATE(self)->token = get_next_token(self);
    } else {
        throw_error("Interpreter::eat_token - Invalid syntax");
    }
}

static double process_factor(Interpreter* self) {
    if (is_addition_operator(self)) {
        return process_unary(self);
    }

    Token* token = get_token(self);
    if (token->get_type(token) == LPAREN) {
        return process_paren(self);
    }

    double result = token->get_payload(token);
    eat_token(self, NUMBER);
    return result;
}

static double process_term(Interpreter* self) {
    double result = process_factor(self);
    while (is_multiplication_operator(self)) {
        result = process_multiplication(self, result);
    }
    return result;
}

static double process_unary(Interpreter* self) {
    Token* token = get_token(self);
    switch (token->get_type(token)) {
        case PLUS:
            eat_token(self, PLUS);
            return process_factor(self);
        case MINUS:
            eat_token(self, MINUS);
            return - process_factor(self);
        default:
            throw_error("Interpreter::process_unary - Invalid syntax");
    }
}

static double process_paren(Interpreter* self) {
    eat_token(self, LPAREN);
    double result = process_expression(self);
    eat_token(self, RPAREN);
    return result;
}

static double process_expression(Interpreter* self) {
    double result = process_term(self);
    while (is_addition_operator(self)) {
        result = process_addition(self, result);
    }
    return result;
}

static double process_addition(Interpreter* self, double initial) {
    Token* token = get_token(self);
    switch (token->get_type(token)) {
        case PLUS:
            eat_token(self, PLUS);
            return initial + process_term(self);
        case MINUS:
            eat_token(self, MINUS);
            return initial - process_term(self);
        default:
            throw_error("Interpreter::process_addition - Invalid syntax");
    }
}

static double process_multiplication(Interpreter* self, double initial) {
    Token* token = get_token(self);
    switch (token->get_type(token)) {
        case MULTIPLICATION:
            eat_token(self, MULTIPLICATION);
            return initial * process_factor(self);
        case DIVISION:
            eat_token(self, DIVISION);
            return initial / process_factor(self);
        default:
            throw_error("Interpreter::process_multiplication - Invalid syntax");
    }
}

MODULE_SET_CONSTRUCTOR(Interpreter, MODULE_INIT_PARAMS(expression), Expression* expression) {
    MODULE_INIT_PRIVATE(Interpreter, self);

    PRIVATE(self)->lexer = Lexer_create(expression);
    PRIVATE(self)->token = get_next_token(self);

    self->process = process_expression;
}

MODULE_SET_DESTRUCTOR(Interpreter) {
    free(PRIVATE(self)->lexer);
    free(PRIVATE(self));
}
