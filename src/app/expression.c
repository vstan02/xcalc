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
#include <string.h>
#include <stdbool.h>

#include "expression.h"

#define PRIVATE(object) ((PRIVATE_DATA*) MODULE_PRIVATE(expression, object))

PRIVATE_DATA {
    size_t length;
    char* target;
};

static void expression_set_size(Expression* self, size_t size) {
    PRIVATE(self)->length = size;
}

size_t expression_get_size(Expression* self) {
    return PRIVATE(self)->length;
}

static bool expression_is_valid_index(Expression* self, size_t index) {
    return index >= 0 && index < expression_get_size(self);
}

static void expression_set_target(Expression* self, char* target) {
    PRIVATE(self)->target = malloc(expression_get_size(self));
    strcpy(PRIVATE(self)->target, target);
}

char expression_get_char(Expression* self, size_t index) {
    if (expression_is_valid_index(self, index)) {
        return PRIVATE(self)->target[index];
    }
    return '\0';
}

MODULE_SET_CONSTRUCTOR(
    expression, Expression,
    MODULE_INIT_PARAMS(string),
    char* string
) {
    MODULE_INIT_PRIVATE(expression, self);
    expression_set_size(self, strlen(string));
    expression_set_target(self, string);
}

MODULE_SET_DESTRUCTOR(expression, Expression) {
    free(PRIVATE(self)->target);
    free(PRIVATE(self));
}
