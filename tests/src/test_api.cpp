#include <catch2/catch_test_macros.hpp>
#include "chaintester.h"
#include "test.h"
#include "utils.h"

#include <eosio/eosio.hpp>
#include "config.hpp"

using namespace eosio;

extern "C" size_t n2s(uint64_t n, char *cstr, size_t length);

static constexpr unsigned int DJBH(const char* cp)
{
  unsigned int hash = 5381;
  while (*cp)
      hash = 33 * hash ^ (unsigned char) *cp++;
  return hash;
}

static constexpr unsigned long long WASM_TEST_ACTION(const char* cls, const char* method)
{
  return static_cast<unsigned long long>(DJBH(cls)) << 32 | static_cast<unsigned long long>(DJBH(method));
}

uint64_t TEST_METHOD(const char* CLASS, const char *METHOD) {
  printf("+++++%s:%s\n", CLASS, METHOD);
  return ( (uint64_t(DJBH(CLASS))<<32) | uint32_t(DJBH(METHOD)) );
}

void CallFunction(ChainTester& tester, uint64_t action, const vector<char>& data, const string& required_exception_type="", const string& exception_message="") {
    auto permissions = R""""(
    {
        "testapi": "active"
    }
    )"""";
    
    auto ret = tester.push_action("testapi", n2s(action), hex_str((uint8_t*)data.data(), data.size()), permissions);
    if (required_exception_type.size() > 0) {
        REQUIRE(ret->HasMember("except"));

        auto& except = (*ret.get())["except"];
        // WARN(JsonToString(except));
        REQUIRE(except["name"].GetString() == required_exception_type);
        if ("wasm_execution_error" == required_exception_type) {
            auto s =  except["stack"][0]["format"].GetString();
            REQUIRE(s == exception_message);
        } else if ("eosio_assert_message_exception" == required_exception_type) {
            auto s =  except["stack"][0]["data"]["s"].GetString();
            REQUIRE(s == exception_message);
        }
    } else {
        // WARN(ret->String());
        REQUIRE(!ret->HasMember("except"));
    }
}

#define CALL_TEST_FUNCTION(_TESTER, CLS, MTH, DATA) CallFunction(_TESTER, TEST_METHOD(CLS, MTH), DATA)
#define CALL_TEST_FUNCTION_AND_CHECK_EXCEPTION(_TESTER, CLS, MTH, DATA, EXCEPT_TYPE, EXCEPT_MSG) CallFunction(_TESTER, TEST_METHOD(CLS, MTH), DATA, EXCEPT_TYPE, EXCEPT_MSG)
#define CALL_TEST_FUNCTION_CHECK_ASSERT_EXCEPTION(_TESTER, CLS, MTH, DATA, EXCEPT_MSG) CallFunction(_TESTER, TEST_METHOD(CLS, MTH), DATA, "eosio_assert_message_exception", EXCEPT_MSG)


TEST_CASE( "test api", "[api]" ) {
    auto pl = vector<permission_level>{{"testapi"_n, config::active_name}};
    vector<char> payload(8192);
    datastream<char*> payload_ds(payload.data(), payload.size());

    bool debug = true;
    ChainTester t(true);
    // load_native_contract(TEST_API_SO);

    SetApplyFn(test_api_native_apply);

    t.enable_debug_contract("testapi", debug);
    auto key = t.create_key();

    auto pub_key = key->GetString("public");
    auto priv_key = key->GetString("private");
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
    SetApplyFn(test_api_native_apply);
    bool debug = true;
    ChainTester t(true);
    t.enable_debug_contract("testapi", debug);
    auto key = t.create_key();

    auto pub_key = key->GetString("public");
    auto priv_key = key->GetString("private");
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

