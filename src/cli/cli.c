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

#include "core/bool.h"
#include "core/file.h"
#include "cli.h"

#define ABOUT_FILE "../assets/about.txt"

struct t_Cli {
    CliApp app;
};

static void cli_run_repl(Cli*);
static void cli_process_args(Cli*, int, const char**);

static void cli_process_input(Cli*, const char*);
static void cli_print_result(double);

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
    while (true) {
        printf("> ");
        getline((char**) &buffer, &size, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        if (!strcmp(buffer, "exit")) return;
        cli_process_input(self, buffer);
    }
}

static void cli_process_args(Cli* self, int argc, const char** argv) {
    if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) {
        printf("%s", file_read_all(ABOUT_FILE));
    }
}

static void cli_process_input(Cli* self, const char* expression) {
    Status status = STATUS_SUCCESS;
    double result = self->app.calculate(expression, &status);
    if (status == STATUS_SUCCESS) {
        cli_print_result(result);
    } else {
        puts("Invalid expression!");
    }
}

static void cli_print_result(double result) {
    printf(result == (int)result ? "= %.0lf\n" : "= %f\n", result);
}
