#include <catch2/catch_test_macros.hpp>
#include <chaintester/chaintester.hpp>
#include <intrinsics.h>
#include "test.h"

TEST_CASE( "test hello", "[hello]" ) {
    // load_native_contract(HELLO_SO);
    ChainTester tester(true);
    tester.set_native_apply("hello"_n, hello_native_apply);

    tester.deploy_contract("hello"_n, HELLO_WASM, HELLO_ABI);

    tester.push_action(
        "hello"_n,
        "hello"_n,
        "sum"_n,
        std::make_tuple(uint64_t(1), uint64_t(2))
    );
    tester.produce_block();
}


TEST_CASE( "test hello shared native lib", "[hello]" ) {

    ChainTester tester(true);
    tester.enable_debugging(true);
    tester.set_native_contract("hello"_n, HELLO_NATIVE_LIB);
    tester.deploy_contract("hello"_n, HELLO_WASM, HELLO_ABI);

    tester.push_action(
        "hello"_n,
        "hello"_n,
        "sum"_n,
        std::make_tuple(uint64_t(1), uint64_t(2))
    );
    tester.produce_block();
}
