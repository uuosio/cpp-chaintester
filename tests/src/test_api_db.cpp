#include <catch2/catch_test_macros.hpp>
#include <chaintester/chaintester.hpp>
#include <intrinsics.h>
#include "test.h"

extern "C" __attribute__ ((visibility ("default"))) void test_api_db_native_apply( uint64_t receiver, uint64_t code, uint64_t action );

TEST_CASE( "test api db", "[api_db]" ) {
    set_native_apply(test_api_db_native_apply);

    ChainTester t(true);

    auto key = t.create_key();
    auto pub_key = key->get_string("public");
    auto priv_key = key->get_string("private");
    t.import_key(pub_key, priv_key);
    t.create_account("eosio"_n, "testapi"_n, pub_key, pub_key);
    t.enable_debug_contract("testapi"_n, is_coverage_enabled());

    t.deploy_contract("testapi"_n, TEST_API_DB_WASM, TEST_API_DB_ABI);


    t.push_action( "testapi"_n, "pg"_n); // primary_i64_general
    t.push_action( "testapi"_n, "pl"_n); // primary_i64_lowerbound
    t.push_action( "testapi"_n, "pu"_n); // primary_i64_upperbound
    t.push_action( "testapi"_n, "s1g"_n); // idx64_general
    t.push_action( "testapi"_n, "s1l"_n); // idx64_lowerbound
    t.push_action( "testapi"_n, "s1u"_n); // idx64_upperbound

   // Store value in primary table
//    t.push_action( "testapi"_n, "tia"_n, "testapi"_n, mutable_variant_object() // test_invalid_access
//       ("code", "testapi")
//       ("val", 10)
//       ("index", 0)
//       ("store", true)
//    );
}
