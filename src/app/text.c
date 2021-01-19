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

#include <malloc.h>
#include <string.h>

#include <core/bool.h>
#include "text.h"

struct t_Text {
    int8_t length;
    const char* target;
};

static bool text_valid_index(const Text*, int8_t);

extern Text* text_create(const char* text) {
    Text* self = (Text*) malloc(sizeof(Text));
    self->length = strlen(text);
    self->target = text;
    return self;
}

extern void text_destroy(Text* self) {
    if (self) free(self);
}

extern int8_t text_get_size(const Text* self) {
    return self->length;
}

extern char text_get_char(const Text* self, int8_t index) {
    return text_valid_index(self, index) ? self->target[index] : '\0';
}

static bool text_valid_index(const Text* self, int8_t index) {
    return index >= 0 && index < self->length;
}
