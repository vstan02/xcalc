/* Status - Error handling
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

#include <stdio.h>
#include <stdlib.h>

#include "status.h"

extern void status_print(status_t status) {
    switch (status) {
        case STATUS_SUCCESS:
            fprintf(stderr, "Success");
            break;
        case STATUS_INVARG:
            fprintf(stderr, "Invalid argument");
            break;
    }
}

extern void status_throw(status_t status) {
    status_print(status);
    exit(EXIT_FAILURE);
}
