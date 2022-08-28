#include <catch2/catch_test_macros.hpp>
#include "chaintester.h"
#include "intrinsics.h"
#include "test.h"

extern "C" __attribute__ ((visibility ("default"))) void test_api_multi_index_native_apply( uint64_t receiver, uint64_t code, uint64_t action );

TEST_CASE( "test multi_index", "[multi_index]" ) {
    set_apply(test_api_multi_index_native_apply);

    ChainTester t(true);

    auto key = t.create_key();
    auto pub_key = key->get_string("public");
    auto priv_key = key->get_string("private");
    t.import_key(pub_key, priv_key);
    t.create_account("eosio", "testapi", pub_key, pub_key);
    t.enable_debug_contract("testapi", true);

    t.deploy_contract("testapi", HELLO_WASM, HELLO_ABI);


    auto perms = R""""(
    {
        "testapi": "active"
    }
    )"""";
    t.push_action("testapi", "s1g", "{}", perms);

}
