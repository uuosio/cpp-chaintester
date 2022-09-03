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

void init_test2(ChainTester& t) {
    set_apply(test_api_native_apply);

    t.enable_debug_contract("testapi", true);

    auto key = t.create_key();
    auto pub_key = key->get_string("public");
    auto priv_key = key->get_string("private");
    t.import_key(pub_key, priv_key);
    t.create_account("eosio", "testapi", pub_key, pub_key);
    t.create_account("eosio", "testapi2", pub_key, pub_key);

    t.deploy_contract("testapi", TEST_API_WASM, TEST_API_ABI);
    t.deploy_contract("testapi2", TEST_API_WASM, TEST_API_ABI);
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

TEST_CASE( "print tests", "[print]" ) {
    ChainTester t(true);
    init_test(t);

	// test prints
    auto ret = CALL_TEST_FUNCTION(t, "test_print", "test_prints", {});
    REQUIRE("abcefg" == ret->get_string("action_traces", 0, "console"));

    // test prints_l
    auto tx2_trace = CALL_TEST_FUNCTION(t, "test_print", "test_prints_l", {});
    auto tx2_act_cnsl = tx2_trace->get_string("action_traces", 0, "console");
    REQUIRE(tx2_act_cnsl == "abatest");

    // test printi
    auto tx3_trace = CALL_TEST_FUNCTION(t, "test_print", "test_printi", {});
    auto tx3_act_cnsl = tx3_trace->get_string("action_traces", 0, "console");
    REQUIRE(tx3_act_cnsl.substr(0,1) == "0");
    REQUIRE(tx3_act_cnsl.substr(1,6) == "556644");
    REQUIRE(tx3_act_cnsl.substr(7, std::string::npos) == "-1");

    // test printui
    auto tx4_trace = CALL_TEST_FUNCTION(t, "test_print", "test_printui", {});
    auto tx4_act_cnsl = tx4_trace->get_string("action_traces", 0, "console");
    REQUIRE(tx4_act_cnsl.substr(0,1) == "0");
    REQUIRE(tx4_act_cnsl.substr(1,6) == "556644");
    REQUIRE(tx4_act_cnsl.substr(7, std::string::npos) == U64Str(-1)); // "18446744073709551615"

    // test printn
    auto tx5_trace = CALL_TEST_FUNCTION(t, "test_print", "test_printn", {});
    auto tx5_act_cnsl = tx5_trace->get_string("action_traces", 0, "console");

    REQUIRE(tx5_act_cnsl.substr(0,1) == "1");
    REQUIRE(tx5_act_cnsl.substr(1,1) == "5");
    REQUIRE(tx5_act_cnsl.substr(2,1) == "a");
    REQUIRE(tx5_act_cnsl.substr(3,1) == "z");

    REQUIRE(tx5_act_cnsl.substr(4,3) == "abc");
    REQUIRE(tx5_act_cnsl.substr(7,3) == "123");

    REQUIRE(tx5_act_cnsl.substr(10,7) == "abc.123");
    REQUIRE(tx5_act_cnsl.substr(17,7) == "123.abc");

    REQUIRE(tx5_act_cnsl.substr(24,13) == "12345abcdefgj");
    REQUIRE(tx5_act_cnsl.substr(37,13) == "ijklmnopqrstj");
    REQUIRE(tx5_act_cnsl.substr(50,13) == "vwxyz.12345aj");

    REQUIRE(tx5_act_cnsl.substr(63, 13) == "111111111111j");
    REQUIRE(tx5_act_cnsl.substr(76, 13) == "555555555555j");
    REQUIRE(tx5_act_cnsl.substr(89, 13) == "aaaaaaaaaaaaj");
    REQUIRE(tx5_act_cnsl.substr(102,13) == "zzzzzzzzzzzzj");

    // test printi128
    auto tx6_trace = CALL_TEST_FUNCTION(t, "test_print", "test_printi128", {} );
    auto tx6_act_cnsl = tx6_trace->get_string("action_traces", 0, "console");
    size_t start = 0;
    size_t end = tx6_act_cnsl.find('\n', start);
    REQUIRE( tx6_act_cnsl.substr(start, end-start) == U128Str(1) );
    start = end + 1; end = tx6_act_cnsl.find('\n', start);
    REQUIRE( tx6_act_cnsl.substr(start, end-start) == U128Str(0) );
    start = end + 1; end = tx6_act_cnsl.find('\n', start);
    REQUIRE( tx6_act_cnsl.substr(start, end-start) == "-" + U128Str(static_cast<unsigned __int128>(std::numeric_limits<__int128>::lowest())) );
    start = end + 1; end = tx6_act_cnsl.find('\n', start);
    REQUIRE( tx6_act_cnsl.substr(start, end-start) == "-" + U128Str(87654323456) );

    // test printui128
    auto tx7_trace = CALL_TEST_FUNCTION(t, "test_print", "test_printui128", {});
    auto tx7_act_cnsl = tx7_trace->get_string("action_traces", 0, "console");
    start = 0; end = tx7_act_cnsl.find('\n', start);
    REQUIRE(tx7_act_cnsl.substr(start, end-start) == U128Str(std::numeric_limits<unsigned __int128>::max()));
    start = end + 1; end = tx7_act_cnsl.find('\n', start);
    REQUIRE(tx7_act_cnsl.substr(start, end-start) == U128Str(0));
    start = end + 1; end = tx7_act_cnsl.find('\n', start);
    REQUIRE(tx7_act_cnsl.substr(start, end-start) == U128Str(87654323456));

    // test printsf
    auto tx8_trace = CALL_TEST_FUNCTION(t, "test_print", "test_printsf", {} );
    auto tx8_act_cnsl = tx8_trace->get_string("action_traces", 0, "console");
    start = 0; end = tx8_act_cnsl.find('\n', start);
    REQUIRE( tx8_act_cnsl.substr(start, end-start) == "5.000000e-01" );
    start = end + 1; end = tx8_act_cnsl.find('\n', start);
    REQUIRE( tx8_act_cnsl.substr(start, end-start) == "-3.750000e+00" );
    start = end + 1; end = tx8_act_cnsl.find('\n', start);
    REQUIRE( tx8_act_cnsl.substr(start, end-start) == "6.666667e-07" );

    // test printdf
    auto tx9_trace = CALL_TEST_FUNCTION(t, "test_print", "test_printdf", {});
    auto tx9_act_cnsl = tx9_trace->get_string("action_traces", 0, "console");
    start = 0; end = tx9_act_cnsl.find('\n', start);
    REQUIRE(tx9_act_cnsl.substr(start, end-start) == "5.000000000000000e-01");
    start = end + 1; end = tx9_act_cnsl.find('\n', start);
    REQUIRE(tx9_act_cnsl.substr(start, end-start) == "-3.750000000000000e+00");
    start = end + 1; end = tx9_act_cnsl.find('\n', start);
    REQUIRE(tx9_act_cnsl.substr(start, end-start) == "6.666666666666666e-07");

    // test printqf
    #ifdef __x86_64__
        std::string expect1 = "5.000000000000000000e-01";
        std::string expect2 = "-3.750000000000000000e+00";
        std::string expect3 = "6.666666666666666667e-07";
    #else
        std::string expect1 = "5.000000000000000e-01";
        std::string expect2 = "-3.750000000000000e+00";
        std::string expect3 = "6.666666666666667e-07";
    #endif
    
    auto tx10_trace = CALL_TEST_FUNCTION(t, "test_print", "test_printqf", {});
    auto tx10_act_cnsl = tx10_trace->get_string("action_traces", 0, "console");
    start = 0; end = tx10_act_cnsl.find('\n', start);
    REQUIRE( tx10_act_cnsl.substr(start, end-start) == expect1 );
    start = end + 1; end = tx10_act_cnsl.find('\n', start);
    REQUIRE( tx10_act_cnsl.substr(start, end-start) == expect2 );
    start = end + 1; end = tx10_act_cnsl.find('\n', start);
    REQUIRE( tx10_act_cnsl.substr(start, end-start) == expect3 );
}

TEST_CASE( "ram_billing_in_notify_tests", "[print]" ) {
    ChainTester t(true);
    init_test2(t);
    // std::array<uint64_t, 2> args = {"testapi"_n.value, "testapi2"_n.value};
    auto args = std::make_tuple("testapi"_n, "testapi2"_n);
    // CALL_TEST_FUNCTION_AND_CHECK_EXCEPTION(t, "test_action", "test_ram_billing_in_notify", eosio::pack(args), "subjective_block_production_exception", "Cannot charge RAM to other accounts during notify."); 
    CALL_TEST_FUNCTION_AND_CHECK_EXCEPTION(t, "test_action", "test_ram_billing_in_notify", eosio::pack(args), "unauthorized_ram_usage_increase", "unprivileged contract cannot increase ${resource} usage of another account within a notify context: ${account}"); 

   CALL_TEST_FUNCTION(t, "test_action", "test_ram_billing_in_notify", eosio::pack(std::make_tuple(uint64_t(0), "testapi2"_n)));
   CALL_TEST_FUNCTION(t, "test_action", "test_ram_billing_in_notify", eosio::pack(std::make_tuple("testapi2"_n, "testapi2"_n)));

// {"code": 3050010,
//   "name": "unauthorized_ram_usage_increase", "message": "Action attempts to increase RAM usage of account without authorization", 
//   "stack": [
//     {
//         "context": {
//             "level": "error", 
//             "file": "apply_context.cpp",
//             "line": 76,
//             "method": "check_unprivileged_resource_usage",
//             "hostname": "",
//             "thread_name": "thread-0",
//             "timestamp": "2022-09-03T07:53:29.043"
//     },
//     "format": "unprivileged contract cannot increase ${resource} usage of another account within a notify context: ${account}",
//     "data": {"resource": "RAM", "account": "testapi"}
//   },
  
//   {
//     "context": {
//         "level": "warn",
//         "file": "apply_context.cpp",
//         "line": 172,
//         "method": "exec_one",
//         "hostname": "",
//         "thread_name": "thread-0", 
//         "timestamp": "2022-09-03T07:53:29.043"
//     },
//     "format": "pending console output: ${console}", 
//     "data": {"console": ""}}  
//   ]

//   }

}

