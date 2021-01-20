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

#include "core/bool.h"
#include "cli.h"

struct t_Cli {
    CliApp app;
};

static void cli_run_repl(Cli*);
static void cli_process_args(Cli*, int, const char**);

static void cli_process_input(Cli*, const char*);
static void cli_print_result(Cli*, double);

extern Cli* cli_create(CliApp app) {
    Cli* self = (Cli*) malloc(sizeof(Cli));
    self->app = app;
    return self;
}

extern void cli_destroy(Cli* self) {
    if (self) free(self);
}

extern void cli_run(Cli* self, int argc, const char** argv) {
    if (self) {
        return argc > 1
            ? cli_process_args(self, argc, argv)
            : cli_run_repl(self);
    }
}

static void cli_run_repl(Cli* self) {
    size_t size = 255;
    char* buffer = (char*) malloc(size);
    printf("Introduce an expression:\n");
    while (true) {
        printf("> ");
        getline((char**) &buffer, &size, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        if (!strcmp(buffer, "exit")) return;
        cli_process_input(self, buffer);
    }
}

static void cli_process_args(Cli* self, int argc, const char** argv) {
    for (size_t index = 0; index < argc; ++index)
        printf("%s\n", argv[index]);
}

static void cli_process_input(Cli* self, const char* expression) {
    Status status = STATUS_SUCCESS;
    double result = self->app.calculate(expression, &status);
    if (status == STATUS_SUCCESS) {
        cli_print_result(self, result);
    } else {
        puts("Invalid expression!");
    }
}

static void cli_print_result(Cli* self, double result) {
    printf(result == (int)result ? "= %.0lf\n" : "= %f\n", result);
}
