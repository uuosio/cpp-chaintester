#pragma once
#include <eosio/name.hpp>
using namespace  eosio;

namespace config {
    const static name system_account_name    { "eosio"_n };
    const static name null_account_name      { "eosio.null"_n };
    const static name producers_account_name { "eosio.prods"_n };

    // Active permission of producers account requires greater than 2/3 of the producers to authorize
    const static name majority_producers_permission_name { "prod.major"_n }; // greater than 1/2 of producers needed to authorize
    const static name minority_producers_permission_name { "prod.minor"_n }; // greater than 1/3 of producers needed to authorize0

    const static name eosio_auth_scope       { "eosio.auth"_n };
    const static name eosio_all_scope        { "eosio.all"_n };

    const static name active_name     { "active"_n };
    const static name owner_name      { "owner"_n };
    const static name eosio_any_name  { "eosio.any"_n };
    const static name eosio_code_name { "eosio.code"_n };

}
