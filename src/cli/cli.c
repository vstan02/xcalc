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
#include "conix.h"

#define ABOUT_FILE "../assets/about.txt"

#define HANDLER(name, data) \
    conix_handler_create((void(*)(void*)) name, data)

struct t_Cli {
    CliApp app;
};

static void cli_run_repl(Cli*);

static void cli_cmd_version(Cli*);
static void cli_cmd_about(Cli*);

static void cli_process_input(Cli*, const char*);

extern Cli* cli_create(CliApp app) {
    Cli* self = (Cli*) malloc(sizeof(Cli));
    self->app = app;
    return self;
}

extern void cli_destroy(Cli* self) {
    if (self) {
        free(self);
    }
}

extern void cli_run(Cli* self, int argc, const char** argv) {
    Conix* conix = conix_create(self->app.name, argc, argv);
    conix_set_default(conix, HANDLER(cli_run_repl, self));
    conix_add_options(conix, 2, (ConixOption[]) {
        { "-v, --version", "Display app version", HANDLER(cli_cmd_version, self) },
        { "-a, --about", "Display other app information", HANDLER(cli_cmd_about, NULL) }
    });
    conix_run(conix);
    conix_destroy(conix);
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

static void cli_cmd_version(Cli* self) {
    printf("%s: v%s\n", self->app.name, self->app.version);
}

static void cli_cmd_about(Cli* self) {
    printf("%s", file_read_all(ABOUT_FILE));
}

static void cli_process_input(Cli* self, const char* expression) {
    Status status = STATUS_SUCCESS;
    double result = self->app.calculate(expression, &status);
    if (status == STATUS_SUCCESS) {
        printf("= %g\n", result);
    } else {
        puts("Invalid expression!");
    }
}
