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

#ifndef XCALC_WINDOW_H
#define XCALC_WINDOW_H

#include "core/module.h"
#include "size.h"

MODULE_CLASS(window, Window, {})

MODULE_CONSTRUCTOR(window, Window, char* title, Size* size)
MODULE_DESTRUCTOR(window, Window)

void window_run(Window* self, int argc, char** argv);

void window_on_close(Window* self, void(*on_close)(void));

#endif // XCALC_WINDOW_H