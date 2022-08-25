#pragma once

#include <stdint.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "intrinsics.h"

typedef void (*fn_native_init)(struct IntrinsicsFuncs* fn);
typedef void (*fn_native_apply)(uint64_t receiver, uint64_t first_receiver, uint64_t action);

typedef void (*fn_apply)(uint64_t receiver, uint64_t first_receiver, uint64_t action);
void SetApplyFn(fn_apply fn);
fn_apply GetApplyFn();

bool load_native_contract(const char *native_contract_path);