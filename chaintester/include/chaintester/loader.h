#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <eosio/eosio.hpp>

struct IntrinsicsFuncs;

typedef void (*fn_native_init)(struct IntrinsicsFuncs* fn);
typedef void (*fn_native_apply)(uint64_t receiver, uint64_t first_receiver, uint64_t action);

typedef void (*fn_apply)(uint64_t receiver, uint64_t first_receiver, uint64_t action);
void set_native_apply(eosio::name contract, fn_apply fn);
fn_apply get_native_apply(eosio::name contract);

bool load_native_contract(const char *native_contract_path);
