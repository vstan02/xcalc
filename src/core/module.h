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

#include <malloc.h>

#include "function.h"

#define PRIVATE_DATA struct Private

#define MODULE_PRIVATE(module, instance) instance->module##_private

#define MODULE_ENUM(main, name) \
    typedef enum t_##main##name main##name; \
    enum t_##main##name

#define MODULE_PARENT(parent) \
    struct t_##parent;

#define MODULE_CLASS(module, class, data) \
    typedef struct t_##class class; \
    struct t_##class { \
        struct data; \
        void* module##_private; \
    };

#define MODULE_CONSTRUCTOR(module, class, args...) \
    class* module##_create(args); \
    void module##_init(class* self, ##args);

#define MODULE_DESTRUCTOR(module, class) \
    void module##_reset(class* self); \
    void module##_destroy(class* self);

#define MODULE_INIT_PRIVATE(module, object) \
    MODULE_PRIVATE(module, self) = (PRIVATE_DATA*) malloc(sizeof(PRIVATE_DATA))

#define MODULE_INIT_PARAMS(args...) (self, ##args)

#define MODULE_SET_CONSTRUCTOR(module, class, init_params, args...) \
    class* module##_create(args) { \
        class* self = (class*) malloc(sizeof(class)); \
        module##_init init_params; \
        return self; \
    } \
    void module##_init(class* self, ##args)

#define MODULE_SET_DESTRUCTOR(module, class) \
    void module##_destroy(class* self) { \
        if (self) { \
            module##_reset(self); \
            free(self); \
        } \
    } \
    void module##_reset(class* self)

#define METHOD_ARGS(class, args...) (class* self, ##args)

#define MODULE_METHOD(module, method, args) \
    FUNCTION_DEF(module##_##method, args)

#define MODULE_IMPL(module, method, args, body) \
    FUNCTION_IMPL(module##_##method, args, body)

#endif // X_CALC_MODULE_H
