/* Lexer - Math expression lexical analyzer
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

#include <stddef.h>

#include "core/status.h"
#include "token.h"

typedef struct t_Lexer Lexer;
typedef struct t_String String;

struct t_String {
    size_t size;
    const char* content;
};

struct t_Lexer {
    char current;
    String expression;
    size_t position;
};

extern void lexer_init(Lexer* lexer, const char* expression);
extern Token lexer_next(Lexer* lexer, Status* status);

#endif // X_CALC_LEXER_H
