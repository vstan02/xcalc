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

#include "expression.h"

#define PRIVATE(object) ((PRIVATE_DATA*) MODULE_PRIVATE(Expression, object))

PRIVATE_DATA {
    size_t length;
    char* target;
};

static void set_size(Expression* self, size_t size) {
    PRIVATE(self)->length = size;
}

static size_t get_size(Expression* self) {
    return PRIVATE(self)->length;
}

static void set_target(Expression* self, char* target) {
    PRIVATE(self)->target = malloc(get_size(self));
    strcpy(PRIVATE(self)->target, target);
}

MODULE_SET_CONSTRUCTOR(Expression, MODULE_INIT_PARAMS(string), char* string) {
    MODULE_INIT_PRIVATE(Expression, self);

    set_size(self, strlen(string));
    set_target(self, string);

    self->get_size = get_size;
}

MODULE_SET_DESTRUCTOR(Expression) {
    free(PRIVATE(self)->target);
    free(PRIVATE(self));
}
