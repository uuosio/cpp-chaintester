#include "test.h"

#include <eosio/eosio.hpp>
#include "config.hpp"

using namespace eosio;

TEST_CASE( "test api", "[api]" ) {
    auto pl = vector<permission_level>{{"testapi"_n, config::active_name}};
    vector<char> payload(8192);
    datastream<char*> payload_ds(payload.data(), payload.size());

    bool debug = true;
    ChainTester t(true);
    // load_native_contract(TEST_API_SO);

    set_apply(test_api_native_apply);

    t.enable_debug_contract("testapi", debug);

    auto key = t.create_key();
    auto pub_key = key->get_string("public");
    auto priv_key = key->get_string("private");
    t.import_key(pub_key, priv_key);
    t.create_account("eosio", "testapi", pub_key, pub_key);

    t.deploy_contract("testapi", TEST_API_WASM, TEST_API_ABI);
    t.produce_block();

    auto args = R""""(
    {
        "nm": "alice"
    }
    )"""";

    CALL_TEST_FUNCTION(t, "test_action", "assert_true", {});
    CALL_TEST_FUNCTION_CHECK_ASSERT_EXCEPTION( t, "test_action", "assert_false", {},
        "test_action::assert_false"
    );

    if (!debug) {
        // test read_action_to_0
        std::vector<char> raw_bytes((1<<16));
        CALL_TEST_FUNCTION( t, "test_action", "read_action_to_0", raw_bytes );

        // test read_action_to_0
        raw_bytes.resize((1<<16)+1);
        CALL_TEST_FUNCTION_AND_CHECK_EXCEPTION(t, "test_action", "read_action_to_0", raw_bytes,
                "wasm_execution_error",
                "access violation"
            );
            t.produce_block();
    }
}

TEST_CASE( "test crypto", "[crypto]" ) {
    // load_native_contract(TEST_API_SO);
    set_apply(test_api_native_apply);
    bool debug = true;
    ChainTester t(true);
    t.enable_debug_contract("testapi", debug);
    auto key = t.create_key();

    auto pub_key = key->get_string("public");
    auto priv_key = key->get_string("private");
    t.import_key(pub_key, priv_key);
    t.create_account("eosio", "testapi", pub_key, pub_key);

    t.deploy_contract("testapi", TEST_API_WASM, TEST_API_ABI);
    t.produce_block();

   CALL_TEST_FUNCTION( t, "test_crypto", "test_sha1", {} );
   CALL_TEST_FUNCTION( t, "test_crypto", "test_sha256", {} );
   CALL_TEST_FUNCTION( t, "test_crypto", "test_sha512", {} );
   CALL_TEST_FUNCTION( t, "test_crypto", "test_ripemd160", {} );
   CALL_TEST_FUNCTION( t, "test_crypto", "sha1_no_data", {} );
   CALL_TEST_FUNCTION( t, "test_crypto", "sha256_no_data", {} );
   CALL_TEST_FUNCTION( t, "test_crypto", "sha512_no_data", {} );
   CALL_TEST_FUNCTION( t, "test_crypto", "ripemd160_no_data", {} );

   CALL_TEST_FUNCTION_AND_CHECK_EXCEPTION( t, "test_crypto", "assert_sha256_false", {},
                                           "crypto_api_exception", "hash mismatch" );

   CALL_TEST_FUNCTION( t, "test_crypto", "assert_sha256_true", {} );

   CALL_TEST_FUNCTION_AND_CHECK_EXCEPTION( t, "test_crypto", "assert_sha1_false", {},
                                           "crypto_api_exception", "hash mismatch" );

   CALL_TEST_FUNCTION( t, "test_crypto", "assert_sha1_true", {} );

   CALL_TEST_FUNCTION_AND_CHECK_EXCEPTION( t, "test_crypto", "assert_sha512_false", {},
                                           "crypto_api_exception", "hash mismatch" );

   CALL_TEST_FUNCTION( t, "test_crypto", "assert_sha512_true", {} );

   CALL_TEST_FUNCTION_AND_CHECK_EXCEPTION( t, "test_crypto", "assert_ripemd160_false", {},
                                           "crypto_api_exception", "hash mismatch" );

   CALL_TEST_FUNCTION( t, "test_crypto", "assert_ripemd160_true", {} );
}

