/* Text - String work routines
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

#ifndef X_CALC_TEXT_H
#define X_CALC_TEXT_H

#include <inttypes.h>

typedef struct t_Text Text;

extern Text* text_create(const char* text);
extern void text_destroy(Text* self);

extern int8_t text_get_size(const Text* self);
extern char text_get_char(const Text* self, int8_t index);

#endif // X_CALC_TEXT_H
