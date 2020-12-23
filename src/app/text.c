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
#include <stdbool.h>

#include "core/private.h"
#include "text.h"

PRIVATE_DATA {
    int8_t length;
    const char* target;
};

static bool text_is_valid_index(Text* self, int8_t index) {
    return index >= 0 && index < PRIVATE(self)->length;
}

int8_t text_get_size(Text* self) {
    return PRIVATE(self)->length;
}

char text_get_char(Text* self, int8_t index) {
    if (text_is_valid_index(self, index)) {
        return PRIVATE(self)->target[index];
    }
    return '\0';
}

void text_init(Text* self, const char* text) {
    PRIVATE_INIT(self);
    PRIVATE(self)->length = strlen(text);
    PRIVATE(self)->target = text;
}

Text* text_create(const char* text) {
    Text* self = (Text*) malloc(sizeof(Text));
    text_init(self, text);
    return self;
}

void text_reset(Text* self) {
    PRIVATE_RESET(self);
}

void text_destroy(Text* self) {
    if (self) {
        text_reset(self);
        free(self);
    }
}
