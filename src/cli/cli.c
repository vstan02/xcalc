/* Cli - Command line interface
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
#include <conix.h>

#include "core/app.h"
#include "core/status.h"
#include "core/bool.h"
#include "app/calc.h"

#include "cli.h"

#define HANDLER(name, data) \
    conix_handler_create((void(*)(void*)) name, data)

static void cli_repl();
static void cli_about(void*);

static void cli_process_input(const char*);

extern void cli_run(int argc, const char** argv) {
    ConixApp app = { APP_NAME, APP_VERSION };
    Conix* conix = conix_create(app, argc, argv);
    conix_add_options(conix, 2, (ConixOption[]) {
        { "-a, --about", "Display other app information", HANDLER(cli_about, NULL) },
        { "--default", "Run app in REPL mode", HANDLER(cli_repl, NULL) }
    });
    conix_run(conix);
    conix_destroy(conix);
}

static void cli_repl(void* data) {
    size_t size = 255;
    char* buffer = (char*) malloc(size);

    while (true) {
        printf("> ");
        getline((char**) &buffer, &size, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        if (strstr(buffer, "exit") != NULL) break;
        cli_process_input(buffer);
    }

    free(buffer);
}

static void cli_about(void* data) {
    printf("%s", APP_ABOUT);
}

static void cli_process_input(const char* expression) {
    Status status = STATUS_SUCCESS;
    double result = calc_calculate(expression, &status);
    if (status == STATUS_SUCCESS) {
        printf("= %g\n", result);
    } else {
        puts("Invalid expression!");
    }
}
