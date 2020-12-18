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

#include "lexer.h"
#include "interpreter.h"

#define PRIVATE(object) ((PRIVATE_DATA*) MODULE_PRIVATE(interpreter, object))

PRIVATE_DATA {
    Lexer* lexer;
    Token* token;
};

static MODULE_METHOD(interpreter, process_unary,METHOD_ARGS(Interpreter, double*))
static MODULE_METHOD(interpreter, process_paren,METHOD_ARGS(Interpreter, double*))
static MODULE_METHOD(interpreter, process_expression,METHOD_ARGS(Interpreter, double*))
static MODULE_METHOD(interpreter, process_addition,METHOD_ARGS(Interpreter, double, double*))
static MODULE_METHOD(interpreter, process_multiplication,METHOD_ARGS(Interpreter, double, double*))

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

static MODULE_IMPL(interpreter, eat_token, METHOD_ARGS(Interpreter, TokenType type), {
    Token *token = interpreter_get_token(self);
    DANGER(token_get_type(token) != type)

    token_destroy(token);
    PRIVATE(self)->token = interpreter_get_next_token(self);
})

static MODULE_IMPL(interpreter, process_factor, METHOD_ARGS(Interpreter, double* result), {
    if (interpreter_is_addition_operator(self)) {
        interpreter_process_unary(self, result);
    }

    Token* token = interpreter_get_token(self);
    if (token_get_type(token) == LPAREN) {
        interpreter_process_paren(self, result);
    }

    *result = token_get_payload(token);
    interpreter_eat_token(self, NUMBER);
})

static MODULE_IMPL(interpreter, process_term, METHOD_ARGS(Interpreter, double* result), {
    interpreter_process_factor(self, result);
    while (interpreter_is_multiplication_operator(self)) {
        interpreter_process_multiplication(self, *result, result);
    }
})

static MODULE_IMPL(interpreter, process_unary, METHOD_ARGS(Interpreter, double* result), {
    TokenType type = token_get_type(interpreter_get_token(self));
    DANGER(type != PLUS && type != MINUS)

    interpreter_eat_token(self, type);
    interpreter_process_term(self, result);
    if (type == MINUS) {
        *result = -*result;
    }
})

static MODULE_IMPL(interpreter, process_paren, METHOD_ARGS(Interpreter, double* result), {
    interpreter_eat_token(self, LPAREN);
    DANGER(interpreter_process_expression(self, result))
    interpreter_eat_token(self, RPAREN);
})

static MODULE_IMPL(interpreter, process_expression, METHOD_ARGS(Interpreter, double* result), {
    interpreter_process_term(self, result);
    while (interpreter_is_addition_operator(self)) {
        interpreter_process_addition(self, *result, result);
    }
})

static MODULE_IMPL(interpreter, process_addition, METHOD_ARGS(Interpreter, double initial, double* result), {
    TokenType type = token_get_type(interpreter_get_token(self));
    DANGER(type != PLUS && type != MINUS)

    interpreter_eat_token(self, type);
    interpreter_process_term(self, result);
    *result = type == PLUS ? initial + *result : initial - *result;
})

static MODULE_IMPL(interpreter, process_multiplication, METHOD_ARGS(Interpreter, double initial, double* result), {
    TokenType type = token_get_type(interpreter_get_token(self));
    DANGER(type != MULTIPLICATION && type != DIVISION)

    interpreter_eat_token(self, type);
    interpreter_process_factor(self, result);
    *result = type == MULTIPLICATION ? initial * *result : initial / *result;
})

MODULE_IMPL(interpreter, process, METHOD_ARGS(Interpreter, double* result), {
    return interpreter_process_expression(self, result);
})

MODULE_SET_CONSTRUCTOR(interpreter, Interpreter, MODULE_INIT_PARAMS(expression), char* expression) {
    MODULE_INIT_PRIVATE(interpreter, self);
    PRIVATE(self)->lexer = lexer_create(expression);
    PRIVATE(self)->token = interpreter_get_next_token(self);
}

MODULE_SET_DESTRUCTOR(interpreter, Interpreter) {
    lexer_destroy(PRIVATE(self)->lexer);
    free(PRIVATE(self));
}
