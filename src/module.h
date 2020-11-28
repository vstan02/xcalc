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

#ifndef X_CALC_MODULE_H
#define X_CALC_MODULE_H

#define PRIVATE_DATA struct Private

#define MODULE_PRIVATE(module, instance) instance->module##_private

#define MODULE_CLASS(module, data) \
    typedef struct t_##module module; \
    struct t_##module { \
        struct data; \
        void* module##_private; \
    };

#define MODULE_CONSTRUCTOR(module, ...) \
    void module##_init(module* self, ##__VA_ARGS__); \
    module* module##_create(__VA_ARGS__);

#define MODULE_DESTRUCTOR(module) \
    void module##_reset(module* self); \
    void module##_destroy(module* self);

#define MODULE(module, data, ...) \
    MODULE_CLASS(module, data) \
    MODULE_CONSTRUCTOR(module, ##__VA_ARGS__) \
    MODULE_DESTRUCTOR(module)

#define MODULE_INIT_PRIVATE(module, object) \
    MODULE_PRIVATE(Expression, self) = (PRIVATE_DATA*) malloc(sizeof(PRIVATE_DATA))

#define MODULE_INIT_PARAMS(...) (self, ##__VA_ARGS__)

#define MODULE_SET_CONSTRUCTOR(module, init_params, ...) \
    module* module##_create(__VA_ARGS__) { \
        module* self = (module*) malloc(sizeof(module)); \
        module##_init init_params; \
        return self; \
    } \
    void module##_init(module* self, ##__VA_ARGS__)

#define MODULE_SET_DESTRUCTOR(module) \
    void module##_destroy(module* self) { \
        if (self) { \
            module##_reset(self); \
            free(self); \
        } \
    } \
    void module##_reset(module* self)

#endif // X_CALC_MODULE_H
