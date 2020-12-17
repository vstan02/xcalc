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

#ifndef XCALC_FUNCTION_H
#define XCALC_FUNCTION_H

#include <stdbool.h>

#define DANGER(condition, body...) \
    if (condition) { \
        body \
        return true; \
    }

#define FUNCTION_DEF(name, args) \
    bool name args;

#define FUNCTION_IMPL(name, args, body) \
    bool name args { \
        body \
        return false; \
    }

#endif // XCALC_FUNCTION_H
