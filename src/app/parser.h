/* Parser - Math expression syntax analyzer
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

#ifndef X_CALC_PARSER_H
#define X_CALC_PARSER_H

#include "core/status.h"
#include "lexer.h"
#include "vars.h"

typedef struct parser parser_t;

struct parser {
    lexer_t lexer;
    status_t status;
    token_t token;
    vars_t* vars;
};

extern void parser_init(parser_t* parser, vars_t* vars, const char* expression);
extern double parser_parse(parser_t* parser, status_t* status);

#endif // X_CALC_PARSER_H
