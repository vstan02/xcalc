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

#include "window.h"

#define PRIVATE(object) ((PRIVATE_DATA*) MODULE_PRIVATE(window, object))

PRIVATE_DATA {
    char* title;
    Size* size;
    GtkWidget* content;
    void (*on_close)(void);
};

void window_set_content(Window* self, GtkWidget* widget) {
    PRIVATE(self)->content = widget;
}

static void window_connect_on_close(Window* self, GtkWidget* target) {
    if (PRIVATE(self)->on_close) {
        g_signal_connect(target, "destroy", G_CALLBACK(PRIVATE(self)->on_close), NULL);
    }
}

static void window_render_content(Window* self, GtkWidget* target) {
    if (PRIVATE(self)->content) {
        gtk_container_add(GTK_CONTAINER(target), PRIVATE(self)->content);
    }
}

void window_run(Window* self) {
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), PRIVATE(self)->title);
    gtk_window_set_default_size(GTK_WINDOW(window), PRIVATE(self)->size->width, PRIVATE(self)->size->height);

    window_render_content(self, window);
    window_connect_on_close(self, window);

    gtk_widget_show_all(window);
}

void window_on_close(Window* self, void(*on_close)(void)) {
    PRIVATE(self)->on_close = on_close;
}

MODULE_SET_CONSTRUCTOR(
    window, Window,
    MODULE_INIT_PARAMS(title, size),
    char* title, Size* size
) {
    MODULE_INIT_PRIVATE(window, self);
    PRIVATE(self)->title = title;
    PRIVATE(self)->size = size;
    PRIVATE(self)->content = NULL;
    PRIVATE(self)->on_close = NULL;
}

MODULE_SET_DESTRUCTOR(window, Window) {
    size_destroy(PRIVATE(self)->size);
    free(PRIVATE(self));
}
