#include <catch2/catch_test_macros.hpp>
#include <chaintester/chaintester.hpp>
#include <intrinsics.h>
#include "test.h"

TEST_CASE( "test hello", "[hello]" ) {
    // load_native_contract(HELLO_SO);
    ChainTester tester(true);
    // tester.set_native_apply("hello"_n, hello_native_apply);

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

extern "C"
{

void say_hello() {
    printf("Hello, World from chaintester api!\n");
}

void* new_chaintester(bool initialize) {
    return new ChainTester(initialize);
}

void free_chaintester(void *tester) {
    delete static_cast<ChainTester*>(tester);
}

size_t chaintester_push_action(void *ptr, char *buffer, size_t buffer_size, const char *account, const char *action, const char *arguments, const char *permissions) {
    ChainTester* tester = static_cast<ChainTester*>(ptr);
    auto ret = tester->push_action_ex(name(account), name(action), arguments, permissions);
    auto& s = ret->to_string();
    size_t copy_size = s.size() > buffer_size ? buffer_size : s.size();
    memcpy(buffer, s.c_str(), s.size());
    return copy_size;
}

size_t chaintester_deploy_contract(void *ptr, char *buffer, size_t buffer_size, const char *account, const char *hex_wasm, const char *hex_abi) {
    ChainTester* tester = static_cast<ChainTester*>(ptr);
    auto ret = tester->deploy_contract_ex(account, hex_wasm, hex_abi);
    auto& s = ret->to_string();
    size_t copy_size = s.size() > buffer_size ? buffer_size : s.size();
    memcpy(buffer, s.c_str(), s.size());
    return copy_size;
}

void chaintester_set_native_apply(void *ptr, char *contract, void *apply) {
    ChainTester* tester = static_cast<ChainTester*>(ptr);
    tester->set_native_apply(name(contract), reinterpret_cast<fn_native_apply>(apply));
}

}
