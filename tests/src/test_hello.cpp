#include <catch2/catch_test_macros.hpp>
#include "chaintester.h"
#include "intrinsics.h"
#include "test.h"

TEST_CASE( "test hello", "[hello]" ) {
    load_native_contract(HELLO_SO);

    ChainTester tester(true);
    tester.enable_debug_contract("hello", true);

    std::vector<char> buffer;
    buffer.resize(512);
    snprintf(buffer.data(), buffer.size(), "%s/%s", APP_PATH, "hello/hello/hello.wasm");
    string wasm_file(buffer.data());

    snprintf(buffer.data(), buffer.size(), "%s/%s", APP_PATH, "hello/hello/hello.abi");
    string abi_file(buffer.data());
    tester.deploy_contract("hello", wasm_file, abi_file);

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
