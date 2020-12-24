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

#ifndef X_CALC_INTERPRETER_H
#define X_CALC_INTERPRETER_H

#include "core/errors.h"

typedef struct t_Interpreter Interpreter;
struct t_Interpreter {
    void* private;
};

double interpreter_process(Interpreter* self, Error* error);

void interpreter_init(Interpreter* self, const char* expression);
Interpreter* interpreter_create(const char* expression);

void interpreter_reset(Interpreter* self);
void interpreter_destroy(Interpreter* self);

#endif // X_CALC_INTERPRETER_H
