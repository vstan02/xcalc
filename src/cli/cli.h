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

#ifndef XCALC_CLI_H
#define XCALC_CLI_H

typedef struct t_Cli Cli;
typedef struct t_CliApp CliApp;

#include "core/status.h"

struct t_CliApp {
    char* name;
    char* version;
    double (*calculate)(const char *expression, Status* status);
};

extern Cli* cli_create(CliApp app);
extern void cli_destroy(Cli* self);

extern void cli_run(Cli* self, int argc, const char** argv);

#endif // XCALC_CLI_H
