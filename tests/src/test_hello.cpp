#include <catch2/catch_test_macros.hpp>
#include <chaintester/chaintester.hpp>
#include <intrinsics.h>
#include "test.h"

TEST_CASE( "test hello", "[hello]" ) {
    // load_native_contract(HELLO_SO);
    ChainTester tester(true);
    tester.set_native_apply("hello"_n, hello_native_apply);

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

    tester.set_native_contract("alice"_n, HELLO_NATIVE_LIB);
    tester.deploy_contract("alice"_n, HELLO_WASM, HELLO_ABI);

    tester.push_action("alice"_n, "alice"_n, "hi"_n, "alice"_n);
    tester.produce_block();
}
