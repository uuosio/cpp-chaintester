#include <catch2/catch_test_macros.hpp>
#include <chaintester.h>
#include <intrinsics.h>
#include "test.h"

extern "C" __attribute__ ((visibility ("default"))) void test_api_db_native_apply( uint64_t receiver, uint64_t code, uint64_t action );

TEST_CASE( "test api db", "[api_db]" ) {
    set_apply(test_api_db_native_apply);

    ChainTester t(true);

    auto key = t.create_key();
    auto pub_key = key->get_string("public");
    auto priv_key = key->get_string("private");
    t.import_key(pub_key, priv_key);
    t.create_account("eosio", "testapi", pub_key, pub_key);
    t.enable_debug_contract("testapi", true);

    t.deploy_contract("testapi", TEST_API_DB_WASM, TEST_API_DB_ABI);


    t.push_action( "testapi", "pg"); // primary_i64_general
    t.push_action( "testapi", "pl"); // primary_i64_lowerbound
    t.push_action( "testapi", "pu"); // primary_i64_upperbound
    t.push_action( "testapi", "s1g"); // idx64_general
    t.push_action( "testapi", "s1l"); // idx64_lowerbound
    t.push_action( "testapi", "s1u"); // idx64_upperbound

   // Store value in primary table
//    t.push_action( "testapi"_n, "tia"_n, "testapi"_n, mutable_variant_object() // test_invalid_access
//       ("code", "testapi")
//       ("val", 10)
//       ("index", 0)
//       ("store", true)
//    );
}
