#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <catch2/catch_test_macros.hpp>

#include "chaintester.h"
#include "intrinsics.h"
#include "test.h"

static void apply(uint64_t receiver, uint64_t first_receiver, uint64_t action) {
    int num = tapos_block_num();
    printi(num);prints("\n");

    int prefix = tapos_block_prefix();
    printi(uint32_t(prefix));prints("\n");
    printui(112233);prints("\n");

    uint32_t time = expiration();
    printi(time);prints("\n");
}

TEST_CASE( "test intrinsics", "[intrinsics]" ) {
    ChainTester tester(true);
    SetApplyFn(apply);
    // tester.enable_debug_contract("hello", true);
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
}
