/* Token - Math expression tokens
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

#include "token.h"

struct t_Token {
    TokenType type;
    double payload;
};

extern Token* token_create(TokenType type, double payload) {
    Token* self = (Token*) malloc(sizeof(Token));
    self->type = type;
    self->payload = payload;
    return self;
}

extern void token_destroy(Token* self) {
    if (self) free(self);
}

extern TokenType token_get_type(const Token* self) {
    return self ? self->type : TOKEN_END;
}

extern double token_get_payload(const Token* self) {
    return self ? self->payload : 0;
}
