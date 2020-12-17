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
#include "lexer.h"
#include "interpreter.h"

#define PRIVATE(object) ((PRIVATE_DATA*) MODULE_PRIVATE(interpreter, object))

PRIVATE_DATA {
    Lexer* lexer;
    Token* token;
};

static double interpreter_process_unary(Interpreter*);
static double interpreter_process_paren(Interpreter*);
static MODULE_METHOD(interpreter, process_expression,METHOD_ARGS(Interpreter, double* result))
static double interpreter_process_addition(Interpreter*, double);
static double interpreter_process_multiplication(Interpreter*, double);

static Token* interpreter_get_next_token(Interpreter* self) {
    return lexer_get_next_token(PRIVATE(self)->lexer);
}

static Token* interpreter_get_token(Interpreter* self) {
    return PRIVATE(self)->token;
}

static bool interpreter_is_addition_operator(Interpreter* self) {
    Token* token = interpreter_get_token(self);
    return token_get_type(token) == PLUS
        || token_get_type(token) == MINUS;
}

static bool interpreter_is_multiplication_operator(Interpreter* self) {
    Token* token = interpreter_get_token(self);
    return token_get_type(token) == MULTIPLICATION
        || token_get_type(token) == DIVISION;
}

static void interpreter_eat_token(Interpreter* self, TokenType type) {
    Token *token = interpreter_get_token(self);
    if (token_get_type(token) == type) {
        token_destroy(token);
        PRIVATE(self)->token = interpreter_get_next_token(self);
    } else {
        throw_error("Interpreter::eat_token - Invalid syntax");
    }
}

static double interpreter_process_factor(Interpreter* self) {
    if (interpreter_is_addition_operator(self)) {
        return interpreter_process_unary(self);
    }

    Token* token = interpreter_get_token(self);
    if (token_get_type(token) == LPAREN) {
        return interpreter_process_paren(self);
    }

    double result = token_get_payload(token);
    interpreter_eat_token(self, NUMBER);
    return result;
}

static double interpreter_process_term(Interpreter* self) {
    double result = interpreter_process_factor(self);
    while (interpreter_is_multiplication_operator(self)) {
        result = interpreter_process_multiplication(self, result);
    }
    return result;
}

static double interpreter_process_unary(Interpreter* self) {
    Token* token = interpreter_get_token(self);
    switch (token_get_type(token)) {
        case PLUS:
            interpreter_eat_token(self, PLUS);
            return interpreter_process_factor(self);
        case MINUS:
            interpreter_eat_token(self, MINUS);
            return -interpreter_process_factor(self);
        default:
            throw_error("Interpreter::process_unary - Invalid syntax");
    }
}

static double interpreter_process_paren(Interpreter* self) {
    interpreter_eat_token(self, LPAREN);
    double result;
    DANGER(interpreter_process_expression(self, &result))
    interpreter_eat_token(self, RPAREN);
    return result;
}

static MODULE_IMPL(interpreter, process_expression, METHOD_ARGS(Interpreter, double* result), {
    *result = interpreter_process_term(self);
    while (interpreter_is_addition_operator(self)) {
        *result = interpreter_process_addition(self, *result);
    }
})

static double interpreter_process_addition(Interpreter* self, double initial) {
    Token* token = interpreter_get_token(self);
    switch (token_get_type(token)) {
        case PLUS:
            interpreter_eat_token(self, PLUS);
            return initial + interpreter_process_term(self);
        case MINUS:
            interpreter_eat_token(self, MINUS);
            return initial - interpreter_process_term(self);
        default:
            throw_error("Interpreter::process_addition - Invalid syntax");
    }
}

static double interpreter_process_multiplication(Interpreter* self, double initial) {
    Token* token = interpreter_get_token(self);
    switch (token_get_type(token)) {
        case MULTIPLICATION:
            interpreter_eat_token(self, MULTIPLICATION);
            return initial * interpreter_process_factor(self);
        case DIVISION:
            interpreter_eat_token(self, DIVISION);
            return initial / interpreter_process_factor(self);
        default:
            throw_error("Interpreter::process_multiplication - Invalid syntax");
    }
}

MODULE_IMPL(interpreter, process, METHOD_ARGS(Interpreter, double* result), {
    return interpreter_process_expression(self, result);
})

MODULE_SET_CONSTRUCTOR(
    interpreter, Interpreter,
    MODULE_INIT_PARAMS(expression),
    char* expression
) {
    MODULE_INIT_PRIVATE(interpreter, self);
    PRIVATE(self)->lexer = lexer_create(expression);
    PRIVATE(self)->token = interpreter_get_next_token(self);
}

MODULE_SET_DESTRUCTOR(interpreter, Interpreter) {
    lexer_destroy(PRIVATE(self)->lexer);
    free(PRIVATE(self));
}
