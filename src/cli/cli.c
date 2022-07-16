/* Cli - Command line interface
 * Copyright (C) 2020-2021 Stan Vlad <vstan02@protonmail.com>
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
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conix.h>

#include "core/app.h"
#include "core/status.h"
#include "app/calc.h"

#include "cli.h"

static void repl_option(cnx_ctx_t*, void*);
static void about_option(cnx_ctx_t*, void*);
static void default_option(cnx_ctx_t*, void*);

static void process_input(const char*);

static bool only_spaces(const char*);

extern void cli_run(size_t argc, const char** argv) {
    cnx_app_t app = { APP_NAME, APP_VERSION };
    cnx_cli_t* cli = cnx_cli_init(app);
    cnx_cli_add(cli, 3, (cnx_option_t[]) {
        { "--default", "Run app in REPL mode", repl_option, NULL },
        { "-a, --about", "Display other app information", about_option, NULL },
        { "*", NULL, default_option, NULL }
    });
    cnx_cli_run(cli, argc, argv);
    cnx_cli_free(cli);
}

static void repl_option(cnx_ctx_t* ctx, void* data) {
    size_t size = 255;
    char* buffer = (char*) malloc(size);

    while (true) {
        printf("> ");
        getline((char**) &buffer, &size, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        if (only_spaces(buffer)) continue;
        if (strstr(buffer, "exit") != NULL) break;
        process_input(buffer);
    }

    free(buffer);
}

static void about_option(cnx_ctx_t* ctx, void* data) {
    printf("%s", APP_ABOUT);
}

static void default_option(cnx_ctx_t* ctx, void* data) {
    printf("%s: Invalid option!\n", APP_NAME);
}

static void process_input(const char* expression) {
    status_t status = STATUS_SUCCESS;
    double result = calc_calculate(expression, &status);
    if (status == STATUS_SUCCESS) {
        printf("= %g\n", result);
    } else {
        printf("Invalid expression!\n");
    }
}

static bool only_spaces(const char* str) {
    while (*str && isspace(*str)) ++str;
    return *str == '\0';
}
