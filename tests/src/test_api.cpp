#include "test.h"

#include <eosio/eosio.hpp>
#include "config.hpp"

using namespace eosio;
void init_test(ChainTester& t) {
    set_apply(test_api_native_apply);

    t.enable_debug_contract("testapi", true);

    auto key = t.create_key();
    auto pub_key = key->get_string("public");
    auto priv_key = key->get_string("private");
    t.import_key(pub_key, priv_key);
    t.create_account("eosio", "testapi", pub_key, pub_key);

    t.deploy_contract("testapi", TEST_API_WASM, TEST_API_ABI);
    t.produce_block();
}

TEST_CASE( "test api", "[api]" ) {
    bool debug = true;
    ChainTester t(true);
    // load_native_contract(TEST_API_SO);
    init_test(t);

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
    init_test(t);

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

TEST_CASE( "test types", "[types]" ) {
    // load_native_contract(TEST_API_SO);
    ChainTester t(true);
    init_test(t);

	CALL_TEST_FUNCTION( t, "test_types", "types_size", {});
	CALL_TEST_FUNCTION( t, "test_types", "char_to_symbol", {});
	CALL_TEST_FUNCTION( t, "test_types", "string_to_name", {});
}

TEST_CASE( "test datastream", "[datastream]" ) {
    // load_native_contract(TEST_API_SO);
    ChainTester t(true);
    init_test(t);
    CALL_TEST_FUNCTION( t, "test_datastream", "test_basic", {} );
}

struct test_permission_last_used_msg {
   eosio::name account;
   eosio::name permission;
   int64_t     last_used_time;

   EOSLIB_SERIALIZE( test_permission_last_used_msg, (account)(permission)(last_used_time) )
};

TEST_CASE( "test account creation time", "[account]" ) {
    // load_native_contract(TEST_API_SO);
    ChainTester t(true);
    init_test(t);
    for (int i=0; i<10; i++) {
        t.produce_block();
    }
    auto ret = t.get_account("testapi");

    auto s = ret->get_string("created");
    CALL_TEST_FUNCTION( t, "test_permission", "test_account_creation_time",
                       eosio::pack<test_permission_last_used_msg>(test_permission_last_used_msg{
                           "testapi"_n, config::active_name,
                           str2ms(s) * 1000
                       }));
}

TEST_CASE( "test permission usage", "[account]" ) {
    // load_native_contract(TEST_API_SO);
    ChainTester t(true);
    init_test(t);
    for (int i=0; i<20; i++) {
        t.produce_block();
    }

    auto ret = t.get_account("testapi");
    auto s = ret->get_string("created");
    CALL_TEST_FUNCTION( t, "test_permission", "test_permission_last_used",
                           eosio::pack<test_permission_last_used_msg>(test_permission_last_used_msg{
                           "testapi"_n, "owner"_n,
                           str2ms(s) * 1000
                       }));
}

struct dummy_action {
   static eosio::name get_name() {
      return "dummyaction"_n;
   }
   static eosio::name get_account() {
      return "testapi"_n;
   }

   char     a; // 1
   uint64_t b; // 8
   int32_t  c; // 4
   EOSLIB_SERIALIZE( dummy_action, (a)(b)(c) )
};

#define DUMMY_ACTION_DEFAULT_A 0x45
#define DUMMY_ACTION_DEFAULT_B 0xab11cd1244556677
#define DUMMY_ACTION_DEFAULT_C 0x7451ae12

TEST_CASE( "test action", "[action]" ) {
    // load_native_contract(TEST_API_SO);
    ChainTester t(true);
    init_test(t);

    auto key = t.create_key();
    auto pub_key = key->get_string("public");
    auto priv_key = key->get_string("private");

    t.import_key(pub_key, priv_key);
    t.create_account("eosio", "acc1", pub_key, pub_key);
    t.create_account("eosio", "acc2", pub_key, pub_key);
    t.create_account("eosio", "acc3", pub_key, pub_key);
    t.create_account("eosio", "acc4", pub_key, pub_key);

    // test assert_true
    CALL_TEST_FUNCTION( t, "test_action", "assert_true", {});

    //test assert_false
    CALL_TEST_FUNCTION_CHECK_ASSERT_EXCEPTION( t, "test_action", "assert_false", {}, "test_action::assert_false");

    dummy_action dummy13{DUMMY_ACTION_DEFAULT_A, DUMMY_ACTION_DEFAULT_B, DUMMY_ACTION_DEFAULT_C};
    CALL_TEST_FUNCTION( t, "test_action", "read_action_normal", eosio::pack<dummy_action>(dummy13));

    // test require_auth
    CALL_TEST_FUNCTION_AND_CHECK_EXCEPTION( t, "test_action", "require_auth", {}, "missing_auth_exception", "missing authority of");

    // test require_auth
    auto a3only = std::vector<eosio::permission_level>{{"acc3"_n, config::active_name}};
    CALL_TEST_FUNCTION_AND_CHECK_EXCEPTION( t, "test_action", "require_auth", eosio::pack(a3only), "missing_auth_exception", "missing authority of");

    auto a4only = std::vector<eosio::permission_level>{{"acc4"_n, config::active_name}};
    CALL_TEST_FUNCTION_AND_CHECK_EXCEPTION( t, "test_action", "require_auth", eosio::pack(a4only), "missing_auth_exception", "missing authority of");

    auto a = TxAction{"testapi", n2s(TEST_METHOD("test_action", "require_auth")), "",
        R"(
            {
                "testapi": "active",
                "acc3": "active",
                "acc4": "active"
            }
        )"};
    t.push_actions({a});
}
