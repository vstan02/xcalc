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
#include "cli.h"
#include "map.h"

#define ABOUT_FILE "../assets/about.txt"

struct t_Cli {
    CliApp app;
    Map* options;
};

static void cli_run_repl(Cli*);
static void cli_process_args(Cli*, int, const char**);

static void cli_add_option(Cli*, const char*, void (*)(void*));
static void cli_cmd_help(Cli*);
static void cli_cmd_version(Cli*);

static void cli_process_input(Cli*, const char*);
static void cli_print_result(double);

extern Cli* cli_create(CliApp app) {
    Cli* self = (Cli*) malloc(sizeof(Cli));
    self->app = app;
    self->options = map_create();
    cli_add_option(self, "--version, -v", (void (*)(void*)) cli_cmd_version);
    return self;
}

extern void cli_destroy(Cli* self) {
    if (self) {
        map_destroy(self->options);
        free(self);
    }
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
    printf("'%s'\n", argv[1]);
    void (*handle)(void*) = (void (*)(void*)) map_get(self->options, argv[1]);
    return handle != NULL ? handle(self) : cli_cmd_help(self);
}

static void cli_add_option(Cli* self, const char* ids, void (*handle)(void*)) {
    char delim[] = ", ";
    size_t size = strlen(ids);
    char target[size + 1];
    strcpy(target, ids);

    char* id = strtok(target, delim);
    while (id) {
        printf("'%s'\n", id);
        map_put(self->options, id, handle);
        id = strtok(NULL, delim);
    }
}

static void cli_cmd_help(Cli* self) {
    printf("I will be happy to help you!\n");
}

static void cli_cmd_version(Cli* self) {
    printf("xCalc: 1.0.0\n");
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
