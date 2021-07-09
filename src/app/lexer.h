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

typedef struct lexer lexer_t;
typedef struct string string_t;

struct string {
    size_t size;
    const char* content;
};

struct lexer {
    char current;
    string_t expression;
    size_t position;
};

extern void lexer_init(lexer_t* lexer, const char* expression);
extern token_t lexer_next(lexer_t* lexer, status_t* status);

#endif // X_CALC_LEXER_H
