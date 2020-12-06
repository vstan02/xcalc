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

#include "calculator.h"
#include "interpreter.h"

double calculator_calculate(Calculator* self, char* expression) {
    Interpreter* interpreter = interpreter_create(expression);
    double result = interpreter_process(interpreter);
    interpreter_destroy(interpreter);
    return result;
}

MODULE_SET_CONSTRUCTOR(calculator, Calculator, MODULE_INIT_PARAMS()) {}
MODULE_SET_DESTRUCTOR(calculator, Calculator) {}
