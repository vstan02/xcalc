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

//#include "cli/cli.h"

#include <stdio.h>
#include <time.h>

#include "app/calc.h"

int main(int argc, const char** argv) {
//    cli_run(argc, argv);
    clock_t start = clock();

    Status status = STATUS_SUCCESS;
    for (size_t i = 0; i < 10000; ++i) {
        calc_calculate("5 + 43 - 3 / 54", &status);
    }

    clock_t end = clock();
    printf("%zu", end - start);
    return 0;
}

// 3802 - 3441
