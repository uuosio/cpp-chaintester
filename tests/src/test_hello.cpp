#include <catch2/catch_test_macros.hpp>
#include <chaintester/chaintester.hpp>
#include <intrinsics.h>
#include "test.h"

TEST_CASE( "test hello", "[hello]" ) {
    // load_native_contract(HELLO_SO);
    set_native_apply(hello_native_apply);

    ChainTester tester(true);
    tester.enable_debug_contract("hello"_n, is_coverage_enabled());

    tester.deploy_contract("hello"_n, HELLO_WASM, HELLO_ABI);

    auto args = R""""(
    {
        "nm": "alice"
    }
    )"""";

    tester.push_action_ex("hello"_n, "hi"_n, args, "hello"_n);
    tester.produce_block();

    args = R""""(
    {
        "nm": "hello"
    }
    )"""";
    tester.push_action_ex("hello"_n, "check"_n, args, "hello"_n);
    tester.produce_block();
}


TEST_CASE( "test hello shared native lib", "[hello]" ) {
    // load_native_contract(HELLO_SO);
    // set_native_apply(hello_native_apply);

    ChainTester tester(true);
    tester.enable_debugging(true);
    tester.set_native_contract("hello"_n, HELLO_NATIVE_LIB);

    tester.deploy_contract("hello"_n, HELLO_WASM, HELLO_ABI);

    auto args = R""""(
    {
        "nm": "alice"
    }
    )"""";

    tester.push_action_ex("hello"_n, "hi"_n, args, "hello"_n);
    tester.produce_block();

    args = R""""(
    {
        "nm": "hello"
    }
    )"""";
    tester.push_action_ex("hello"_n, "check"_n, args, "hello"_n);
    tester.produce_block();
}
