/* xCalc - A fast and simple to use calculator
 * Copyright (C) 2020-2023 Stan Vlad <vstan02@protonmail.com>
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
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include <conix.h>
#include <arithmo.h>

#define APP_NAME "xcalc"
#define APP_VERSION "0.2.1"

#define APP_ABOUT \
  "xCalc - A fast and simple to use calculator\n" \
  "Copyright (C) 2020-2023 Stan Vlad <vstan02@protonmail.com>\n\n" \
  "This program comes with ABSOLUTELY NO WARRANTY.\n" \
  "This is free software, and you are welcome to redistribute\n" \
  "it under certain conditions.\n" \
  "See <https://www.gnu.org/licenses/> for more details.\n"

#define VAR_TABLE_SIZE 10

static void repl_option(cnx_ctx_t*, void*);
static void about_option(cnx_ctx_t*, void*);
static void default_option(cnx_ctx_t*, void*);

static void process_input(artm_calc_t*, const char*);

static bool only_spaces(const char*);

extern int main(int argc, const char** argv) {
  cnx_app_t app = { APP_NAME, APP_VERSION };
  cnx_cli_t* cli = cnx_cli_init(app);

  cnx_cli_add(cli, 3, (cnx_option_t[]) {
    { "--default", "Run app in REPL mode", repl_option, NULL },
    { "-a, --about", "Display other app information", about_option, NULL },
    { "*", NULL, default_option, NULL }
  });

  cnx_cli_run(cli, argc, argv);
  cnx_cli_free(cli);
  return 0;
}

static void repl_option(
  __attribute_maybe_unused__ cnx_ctx_t* ctx,
  __attribute_maybe_unused__ void* data
) {
  artm_calc_t* calc = artm_calc_init(VAR_TABLE_SIZE);

  size_t size = 255;
  char* buffer = (char*) malloc(size);

  while (true) {
    printf("> ");
    getline((char**) &buffer, &size, stdin);
    buffer[strlen(buffer) - 1] = '\0';
    if (only_spaces(buffer)) continue;
    if (strstr(buffer, "exit") != NULL) break;
    process_input(calc, buffer);
  }

  free(buffer);
  artm_calc_free(calc);
}

static void about_option(
  __attribute_maybe_unused__ cnx_ctx_t* ctx,
  __attribute_maybe_unused__ void* data
) {
  printf("%s", APP_ABOUT);
}

static void default_option(
  __attribute_maybe_unused__ cnx_ctx_t* ctx,
  __attribute_maybe_unused__ void* data
) {
  printf("%s: Invalid option!\n", APP_NAME);
}

static void process_input(artm_calc_t* calc, const char* expression) {
  artm_result_t result = artm_calc_eval(calc, expression);
  switch (result.status) {
    case ARTM_SUCCESS:
      printf("= %g\n", result.as.value);
      break;
    case ARTM_INV_TOKEN: {
      const artm_token_t* tkn = &result.as.token;
      printf("Invalid token: '%.*s'.\n", (int)tkn->size, tkn->target);
      break;
    }
    case ARTM_UNDEF_VAR: {
      const artm_token_t* tkn = &result.as.token;
      printf("Undefined variable: '%.*s'.\n", (int)tkn->size, tkn->target);
      break;
    }
    default:
      printf("Internal error.\n");
  }
}

static bool only_spaces(const char* str) {
  while (*str && isspace(*str)) ++str;
  return *str == '\0';
}
