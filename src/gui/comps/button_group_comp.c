/**
 * xCalc - A fast and simple to use calculator
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

#include <stdarg.h>

#include "button_group_comp.h"
#include "button_comp.h"

static GtkWidget* button_row_create(short count, ...) {
    va_list args;
    va_start(args, count);
    GtkWidget* row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    for (short i = 0; i < count; ++i) {
        GtkWidget* button = button_comp_create(va_arg(args, char*));
        gtk_box_pack_start(GTK_BOX(row), button, TRUE, TRUE, 10);
    }
    va_end(args);
    return row;
}

static void button_group_add_row(GtkWidget* group, GtkWidget* row) {
    gtk_box_pack_start(GTK_BOX(group), row, TRUE, TRUE, 10);
}

GtkWidget* button_group_comp_create(void) {
    GtkWidget* group = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    button_group_add_row(group, button_row_create(3, "1", "2", "3"));
    button_group_add_row(group, button_row_create(3, "4", "5", "6"));
    button_group_add_row(group, button_row_create(3, "7", "8", "9"));
    button_group_add_row(group, button_row_create(3, "+", "0", "*"));
    button_group_add_row(group, button_row_create(3, "-", "=", "/"));
    return group;
}
