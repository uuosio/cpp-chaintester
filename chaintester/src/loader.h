#pragma once

#include <stdint.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

struct IntrinsicsFuncs;

typedef void (*fn_native_init)(struct IntrinsicsFuncs* fn);
typedef void (*fn_native_apply)(uint64_t receiver, uint64_t first_receiver, uint64_t action);

typedef void (*fn_apply)(uint64_t receiver, uint64_t first_receiver, uint64_t action);
void set_apply(fn_apply fn);
fn_apply get_apply();

bool load_native_contract(const char *native_contract_path);
