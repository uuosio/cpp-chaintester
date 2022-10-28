#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct IntrinsicsFuncs;

typedef void (*fn_native_init)(struct IntrinsicsFuncs* fn);
typedef void (*fn_native_apply)(uint64_t receiver, uint64_t first_receiver, uint64_t action);
