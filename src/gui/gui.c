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

#include <gtk/gtk.h>

#include "gui.h"

#define PRIVATE(object) ((PRIVATE_DATA*) MODULE_PRIVATE(gui, object))

PRIVATE_DATA {
    App* app;
};

void gui_run(Gui* self, int argc, char** argv) {
    gtk_init(&argc, &argv);
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(window), "xCalc");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    gtk_widget_show_all(window);
    gtk_main();
}

MODULE_SET_CONSTRUCTOR(gui, Gui, MODULE_INIT_PARAMS(app), App* app) {
    MODULE_INIT_PRIVATE(gui, self);
    PRIVATE(self)->app = app;
}

MODULE_SET_DESTRUCTOR(gui, Gui) {
    free(PRIVATE(self));
}
