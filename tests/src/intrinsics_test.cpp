#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <catch2/catch_test_macros.hpp>

#include <chaintester/chaintester.hpp>
#include <intrinsics.h>
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
    set_native_apply(apply);
    // tester.enable_debug_contract("hello", true);
    tester.enable_debug_contract("hello"_n, is_coverage_enabled());
    tester.deploy_contract("hello"_n, HELLO_WASM, HELLO_ABI);

    auto args = R""""(
    {
        "nm": "alice"
    }
    )"""";

    tester.push_action_ex("hello"_n, "hi"_n, args, "hello"_n);
    tester.produce_block();
}
