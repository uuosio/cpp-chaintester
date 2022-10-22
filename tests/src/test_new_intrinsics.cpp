#include <catch2/catch_test_macros.hpp>
#include <chaintester.h>
#include <intrinsics.h>
#include "test.h"
#include <eosio/eosio.hpp>

extern "C" __attribute__ ((visibility ("default"))) void new_intrinsics_native_apply( uint64_t receiver, uint64_t code, uint64_t action );

struct TestArgs {
    uint64_t block_num;
    EOSLIB_SERIALIZE(TestArgs, (block_num))
};

TEST_CASE( "test_new_intrinsics", "[new intrinsics]" ) {
    // load_native_contract(HELLO_SO);
    set_native_apply(new_intrinsics_native_apply);

    ChainTester tester(true);
    tester.enable_debug_contract("hello"_n, true);

    tester.deploy_contract("hello"_n, HELLO_WASM, HELLO_ABI);
    auto info = tester.get_info();
    // WARN(info->to_string());
    WARN(info->get_uint64("head_block_num"));
    auto head_block_num = info->get_uint64("head_block_num");

    auto args = eosio::pack(
        TestArgs{
            head_block_num + 1
        }
    );

    auto ret = tester.push_action("hello"_n, "test"_n, args, "hello"_n);
    tester.produce_block();
    // WARN(ret->to_string());
    REQUIRE(ret->get_string("action_traces", 0, "return_value") == hex_str((uint8_t*)"helloworld", 10));
}
