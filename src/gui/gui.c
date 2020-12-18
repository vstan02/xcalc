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
#include "window.h"
#include "comps/root_comp.h"

#define WIN_TITLE "xCalc"
#define WIN_WIDTH 300
#define WIN_HEIGHT 360

#define PRIVATE(object) ((PRIVATE_DATA*) MODULE_PRIVATE(gui, object))

PRIVATE_DATA {
    App* app;
    Window* window;
};

static Window* gui_window_create(void) {
    Window* window = window_create(WIN_TITLE, size_create(WIN_WIDTH, WIN_HEIGHT));
    window_on_close(window, gtk_main_quit);
    return window;
}

void gui_run(Gui* self, int argc, char** argv) {
    gtk_init(&argc, &argv);
    window_set_content(PRIVATE(self)->window, root_comp_create());
    window_run(PRIVATE(self)->window);
    gtk_main();
}

MODULE_SET_CONSTRUCTOR(gui, Gui, MODULE_INIT_PARAMS(app), App* app) {
    MODULE_INIT_PRIVATE(gui, self);
    PRIVATE(self)->app = app;
    PRIVATE(self)->window = gui_window_create();
}

MODULE_SET_DESTRUCTOR(gui, Gui) {
    window_destroy(PRIVATE(self)->window);
    free(PRIVATE(self));
}
