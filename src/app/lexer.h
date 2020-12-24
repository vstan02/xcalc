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

#ifndef X_CALC_LEXER_H
#define X_CALC_LEXER_H

#include "core/errors.h"

#include "token.h"

typedef struct t_Lexer Lexer;
struct t_Lexer {
    void* private;
};

Token* lexer_get_next(Lexer* self, Error* error);

void lexer_init(Lexer* self, const char* expression);
Lexer* lexer_create(const char* expression);

void lexer_reset(Lexer* self);
void lexer_destroy(Lexer* self);

#endif // X_CALC_LEXER_H
