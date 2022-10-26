#pragma once

#include <cstdlib>
#include <optional>

#include <eosio/eosio.hpp>
#include <eosio/privileged.hpp>
#include <eosio/asset.hpp>
#include <eosio/crypto.hpp>

#include <chaintester/base58.hpp>

using namespace eosio;

struct permission_level_weight {
    permission_level  permission;
    uint16_t          weight;

    // explicit serialization macro is not necessary, used here only to improve compilation time
    EOSLIB_SERIALIZE( permission_level_weight, (permission)(weight) )
};

// struct key_weight {
//     eosio::public_key  key;
//     uint16_t           weight;

//     // explicit serialization macro is not necessary, used here only to improve compilation time
//     EOSLIB_SERIALIZE( key_weight, (key)(weight) )
// };

struct wait_weight {
    uint32_t           wait_sec;
    uint16_t           weight;

    // explicit serialization macro is not necessary, used here only to improve compilation time
    EOSLIB_SERIALIZE( wait_weight, (wait_sec)(weight) )
};

struct authority {
    uint32_t                              threshold = 0;
    std::vector<key_weight>               keys;
    std::vector<permission_level_weight>  accounts;
    std::vector<wait_weight>              waits;

    // explicit serialization macro is not necessary, used here only to improve compilation time
    EOSLIB_SERIALIZE( authority, (threshold)(keys)(accounts)(waits) )
};

struct newaccount{
    name creator;
    name name;
    authority owner;
    authority active;
};

static authority create_authority( const string& pub, optional<permission_level_weight> perm = std::nullopt ) {
    return authority{
        .threshold = 1,
        .keys = {
            {
                .key = decode_public_key(pub),
                .weight = 1
            }
        },
        .accounts = perm.has_value() ? vector<permission_level_weight>({perm.value()}) : vector<permission_level_weight>(),
        .waits = {}
    };
}
