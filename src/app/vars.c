/* Vars - A collection of variables
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

#include <malloc.h>
#include <string.h>

#include "vars.h"

struct vars_store {
    char* name;
    double value;
    vars_store_t* next;
};

static size_t hash(const char* target);

extern void vars_init(vars_t* vars) {
    for (size_t i = 0; i < STORES_SIZE; ++i) {
        vars->stores[i] = NULL;
    }
}

extern void vars_free(vars_t* vars) {
    for (size_t i = 0; i < STORES_SIZE; ++i) {
        while (vars->stores[i] != NULL) {
            vars_store_t* store = vars->stores[i];
            vars->stores[i] = vars->stores[i]->next;
            free(store->name);
            free(store);
        }
    }
}

extern void vars_set(vars_t* vars, const char* name, double value) {
    size_t index = hash(name);
    vars_store_t* store = (vars_store_t*) malloc(sizeof(vars_store_t));
    store->name = strdup(name);
    store->value = value;
    store->next = vars->stores[index];
    vars->stores[index] = store;
}

extern double* vars_get(vars_t* vars, const char* name) {
    size_t index = hash(name);
    vars_store_t* store = vars->stores[index];
    while (store != NULL) {
        if (!strcmp(store->name, name)) {
            return &store->value;
        }
        store = store->next;
    }
    return NULL;
}

static size_t hash(const char* target) {
    size_t result = 0;
    while (*target != '\0') result += *(target++);
    return result % STORES_SIZE;
}
