/* Vars - A collection of variables
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

#ifndef XCALC_VARS_H
#define XCALC_VARS_H

#include "core/status.h"

#define STORES_SIZE 20

typedef struct vars vars_t;
typedef struct vars_store vars_store_t;

struct vars {
    vars_store_t* stores[20];
};

extern void vars_init(vars_t* vars);
extern void vars_free(vars_t* vars);

extern double* vars_get(vars_t* vars, const char* name);
extern void vars_set(vars_t* vars, const char* name, double value);

#endif // XCALC_VARS_H
