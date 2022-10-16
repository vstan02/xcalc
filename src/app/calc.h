/* Calc - Math expression calculator
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

#ifndef XCALC_CALC_H
#define XCALC_CALC_H

#include "core/status.h"
#include "parser.h"
#include "vars.h"

typedef struct calc calc_t;

struct calc {
    vars_t vars;
    parser_t parser;
};

extern void calc_init(calc_t* calc);
extern void calc_free(calc_t* calc);

extern double calc_calculate(calc_t* calc, const char* expression, status_t* status);

#endif // XCALC_CALC_H
