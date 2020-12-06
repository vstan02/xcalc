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

#include "app/calculator.h"
#include "gui/gui.h"

double app_calculate(App* app, char* expression) {
    calculator_calculate((Calculator*) app, expression);
}

int main(int argc, char** argv) {
    Calculator* calculator = calculator_create();
    Gui* ui = gui_create((App*) calculator);
    gui_run(ui, argc, argv);
    gui_destroy(ui);
    calculator_destroy(calculator);
    return 0;
}
