#include <cstdlib>
#include <eosio/eosio.hpp>
#include <eosio/privileged.hpp>

#include "config.hpp"
#include "test.h"

using namespace eosio;

void update_auth(ChainTester& t, string pub_key) {
    const char* updateauth_args = R"(
    {
        "account": "testapi",
        "permission": "active",
        "parent": "owner",
        "auth": {
            "threshold": 1,
            "keys": [
                {
                    "key": "%s",
                    "weight": 1
                }
            ],
            "accounts": [{"permission":{"actor": "testapi", "permission": "eosio.code"}, "weight":1}],
            "waits": []
        }
    }
    )";
    char _updateauth_args[strlen(updateauth_args) + pub_key.size()+1];
    snprintf(_updateauth_args, sizeof(_updateauth_args), updateauth_args, pub_key.c_str());

    string permissions = R"(
        {
            "testapi": "active"
        }
    )";
    t.push_action_ex("eosio"_n, "updateauth"_n, string(_updateauth_args), permissions);
    t.produce_block();
}

void init_test(ChainTester& t) {
    set_native_apply(test_api_native_apply);

    const char * TEST_COVERAGE = std::getenv("TEST_COVERAGE");
    if (TEST_COVERAGE == nullptr || string("") == TEST_COVERAGE || string("0") == TEST_COVERAGE || string("FALSE") == TEST_COVERAGE) {
        t.enable_debug_contract("testapi"_n, false);
    } else if (string("1") == TEST_COVERAGE || string("TRUE") == TEST_COVERAGE) {
        t.enable_debug_contract("testapi"_n, true);
    } else {
        throw std::runtime_error("Invalid TEST_COVERAGE ENV");
    }

    auto key = t.create_key();
    auto pub_key = key->get_string("public");
    auto priv_key = key->get_string("private");
    t.import_key(pub_key, priv_key);
    t.create_account("eosio"_n, "testapi"_n, pub_key, pub_key);
    
    update_auth(t, pub_key);

    t.deploy_contract("testapi"_n, TEST_API_WASM, TEST_API_ABI);
    t.produce_block();
}

void init_test2(ChainTester& t) {
    set_native_apply(test_api_native_apply);

    t.enable_debug_contract("testapi"_n, true);

    auto key = t.create_key();
    auto pub_key = key->get_string("public");
    auto priv_key = key->get_string("private");
    t.import_key(pub_key, priv_key);
    t.create_account("eosio"_n, "testapi"_n, pub_key, pub_key);
    t.create_account("eosio"_n, "testapi2"_n, pub_key, pub_key);

    t.deploy_contract("testapi"_n, TEST_API_WASM, TEST_API_ABI);
    t.deploy_contract("testapi2"_n, TEST_API_WASM, TEST_API_ABI);
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
    set_native_apply(test_api_native_apply);
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
    auto ret = t.get_account("testapi"_n);

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

    auto ret = t.get_account("testapi"_n);
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
    t.create_account("eosio"_n, "acc1"_n, pub_key, pub_key);
    t.create_account("eosio"_n, "acc2"_n, pub_key, pub_key);
    t.create_account("eosio"_n, "acc3"_n, pub_key, pub_key);
    t.create_account("eosio"_n, "acc4"_n, pub_key, pub_key);

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

    auto a = action{
        vector<permission_level>(
        {
            {"testapi"_n, "active"_n},
            {"acc3"_n, "active"_n},
            {"acc4"_n, "active"_n}
        }),
        "testapi"_n,
        name(TEST_METHOD("test_action", "require_auth")),
        std::make_tuple()
    };
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
    CALL_TEST_FUNCTION_AND_CHECK_EXCEPTION(t, "test_action", "test_ram_billing_in_notify", eosio::pack(args), "unauthorized_ram_usage_increase", "unprivileged contract cannot increase RAM usage of another account within a notify context: ${account}"); 

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

TEST_CASE( "test transaction", "[transaction]" ) {
    ChainTester t(true);
    init_test(t);

	// test prints
    auto ret = CALL_TEST_FUNCTION(t, "test_transaction", "test_read_transaction", {});
    WARN(ret->get_string("action_traces", 0, "console"));

    auto info = t.get_info();
    // WARN(info->to_string());
    auto num = info->get_uint64("last_irreversible_block_num");
    CALL_TEST_FUNCTION(t, "test_transaction", "test_tapos_block_num", eosio::pack((int32_t)num));

    auto last_irreversible_block_id = hex2bytes(info->get_string("last_irreversible_block_id"));
    uint64_t hash[4];
    memcpy(hash, last_irreversible_block_id.data(), last_irreversible_block_id.size());
    CALL_TEST_FUNCTION(t, "test_transaction", "test_tapos_block_prefix", eosio::pack(hash[1]));

    CALL_TEST_FUNCTION_AND_CHECK_EXCEPTION(t, "test_transaction", "send_action_recurse", {}, "transaction_exception", "max inline action depth per transaction reached");

    CALL_TEST_FUNCTION(t, "test_transaction", "send_transaction", {});
    t.produce_block();
    t.produce_block();
}

TEST_CASE( "test chain", "[chain]" ) {
    ChainTester t(false);
    set_native_apply(test_api_native_apply);

    t.enable_debug_contract("testapi"_n, true);

    string permissions = R"(
        {
            "eosio": "active"
        }
    )";

    string args = R"(
        {
            "creator": "eosio",
            "name": "%s",
            "owner": {
                "threshold": 1,
                "keys": [{"key": "EOS6AjF6hvF7GSuSd4sCgfPKq5uWaXvGM2aQtEUCwmEHygQaqxBSV", "weight": 1}],
                "accounts": [],
                "waits": []
            },
            "active": {
                "threshold": 1,
                "keys": [{"key": "EOS6AjF6hvF7GSuSd4sCgfPKq5uWaXvGM2aQtEUCwmEHygQaqxBSV", "weight": 1}],
                "accounts": [],
                "waits": []
            }
        }
    )";
    char buffer[args.size() + 13 + 1];
    snprintf(buffer, sizeof(buffer), args.c_str(), "testapi");

    t.push_action_ex("eosio"_n, "newaccount"_n, string(buffer), permissions);

    string pub_key = "EOS6AjF6hvF7GSuSd4sCgfPKq5uWaXvGM2aQtEUCwmEHygQaqxBSV";

    vector<string> producers = { "inita",
                                "initb",
                                "initc",
                                "initd",
                                "inite",
                                "initf",
                                "initg",
                                "inith",
                                "initi",
                                "initj",
                                "initk",
                                "initl",
                                "initm",
                                "initn",
                                "inito",
                                "initp",
                                "initq",
                                "initr",
                                "inits",
                                "initt",
                                "initu"
    };

    for (auto& a: producers) {
        snprintf(buffer, sizeof(buffer), args.c_str(), a.c_str());
        t.push_action_ex("eosio"_n, "newaccount"_n, string(buffer), permissions);
        t.produce_block();
    }
    t.deploy_contract("eosio"_n, ACTIVATE_WASM, ACTIVATE_ABI);

    vector<string> feature_digests = {
        "1a99a59d87e06e09ec5b028a9cbb7749b4a5ad8819004365d02dc4379a8b7241", //ONLY_LINK_TO_EXISTING_PERMISSION" 
        "2652f5f96006294109b3dd0bbde63693f55324af452b799ee137a81a905eed25", //"FORWARD_SETCODE"
        "299dcb6af692324b899b39f16d5a530a33062804e41f09dc97e9f156b4476707", //"WTMSIG_BLOCK_SIGNATURES"
        "35c2186cc36f7bb4aeaf4487b36e57039ccf45a9136aa856a5d569ecca55ef2b", //"GET_BLOCK_NUM"
        "ef43112c6543b88db2283a2e077278c315ae2c84719a8b25f25cc88565fbea99", //"REPLACE_DEFERRED"
        "4a90c00d55454dc5b059055ca213579c6ea856967712a56017487886a4d4cc0f", //"NO_DUPLICATE_DEFERRED_ID"
        "4e7bf348da00a945489b2a681749eb56f5de00b900014e137ddae39f48f69d67", //"RAM_RESTRICTIONS"
        "4fca8bd82bbd181e714e283f83e1b45d95ca5af40fb89ad3977b653c448f78c2", //"WEBAUTHN_KEY"
        "5443fcf88330c586bc0e5f3dee10e7f63c76c00249c87fe4fbf7f38c082006b4", //"BLOCKCHAIN_PARAMETERS"
        "68dcaa34c0517d19666e6b33add67351d8c5f69e999ca1e37931bc410a297428", //"DISALLOW_EMPTY_PRODUCER_SCHEDULE"
        "6bcb40a24e49c26d0a60513b6aeb8551d264e4717f306b81a37a5afb3b47cedc", //"CRYPTO_PRIMITIVES"
        "8ba52fe7a3956c5cd3a656a3174b931d3bb2abb45578befc59f283ecd816a405", //"ONLY_BILL_FIRST_AUTHORIZER"
        "ad9e3d8f650687709fd68f4b90b41f7d825a365b02c23a636cef88ac2ac00c43", //"RESTRICT_ACTION_TO_SELF"
        "bcd2a26394b36614fd4894241d3c451ab0f6fd110958c3423073621a70826e99", //"GET_CODE_HASH"
        "c3a6138c5061cf291310887c0b5c71fcaffeab90d5deb50d3b9e687cead45071", //"ACTION_RETURN_VALUE"
        "d528b9f6e9693f45ed277af93474fd473ce7d831dae2180cca35d907bd10cb40", //"CONFIGURABLE_WASM_LIMITS2"
        "e0fb64b1085cc5538970158d05a009c24e276fb94e1a0bf6a528b48fbc4ff526", //"FIX_LINKAUTH_RESTRICTION"
        "f0af56d2c5a48d60a4a5b5c903edfb7db3a736a94ed589d0b797df33ff9d3e1d", //"GET_SENDER"
    };

    for (auto& digest: feature_digests) {
        snprintf(buffer, sizeof(buffer), R"({"feature_digest": "%s"})", digest.c_str());
        t.push_action_ex("eosio"_n, "activate"_n, string(buffer), permissions);
    }
    t.produce_block();

    t.deploy_contract("eosio"_n, BIOS_WASM, BIOS_ABI);
    t.produce_block();

    t.deploy_contract("testapi"_n, TEST_API_WASM, TEST_API_ABI);
    t.produce_block();

    ecc_public_key _key;
    //EOS6AjF6hvF7GSuSd4sCgfPKq5uWaXvGM2aQtEUCwmEHygQaqxBSV
    memcpy(_key.data(), "\x02\xa8\x91\xe0\xdd\x57\x13\x2e\xd6\x83\xbc\x87\x5d\xac\xc9\x61\xc6\xfd\x5d\xfa\xe6\x80\x0b\xc6\x18\x1a\xb6\x8b\xb8\x48\x25\x1e\x52", 33);
    public_key key{std::in_place_index<0>, _key};

    std::vector<producer_authority> prods;
    for (auto& a: producers) {
        prods.emplace_back(producer_authority{
            .producer_name = eosio::name(a),
            .authority = block_signing_authority_v0{
                .threshold = 1,
                .keys = {
                    key_weight{
                        .key = key,
                        .weight = 1,
                    }
                }
            }
        });
    }

    auto ret = t.push_action_ex("eosio"_n, "setprods"_n, eosio::pack(prods));
    // WARN(ret->to_string());
    for (int i=0; i<200; i++) {
        t.produce_block();
    }

    vector<eosio::name> prod_names(producers.size());
    for ( uint32_t i = 0; i < producers.size(); i++ ) {
        prod_names[i] = name(producers[i]);
    }

    CALL_TEST_FUNCTION(t, "test_chain", "test_activeprods", eosio::pack(prod_names));
    // WARN(ret->to_string());
}
