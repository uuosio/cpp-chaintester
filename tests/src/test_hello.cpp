#include <catch2/catch_test_macros.hpp>
#include "chaintester.h"
#include "intrinsics.h"
#include "test.h"

TEST_CASE( "test hello", "[hello]" ) {
    // load_native_contract(HELLO_SO);
    set_apply(hello_native_apply);

    ChainTester tester(true);
    tester.enable_debug_contract("hello", true);

    tester.deploy_contract("hello", HELLO_WASM, HELLO_ABI);

    auto args = R""""(
    {
        "nm": "alice"
    }
    )"""";

    auto permissions = R""""(
    {
        "hello": "active"
    }
    )"""";
    tester.push_action("hello", "hi", args, permissions);
    tester.produce_block();

    args = R""""(
    {
        "nm": "hello"
    }
    )"""";
    tester.push_action("hello", "check", args, permissions);
    tester.produce_block();
}
