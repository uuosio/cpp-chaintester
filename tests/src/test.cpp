#include "chaintester.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <catch2/catch_test_macros.hpp>

#include "test.h"

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    ChainTester tester(true);

    // tester.enable_debug_contract("hello", true);
    tester.enable_debug_contract("helloworld33", true);

    auto key = tester.create_key();
    std::cout<<key.String()<<std::endl;

    auto pub_key = key.GetString("public");
    auto priv_key = key.GetString("private");
    tester.import_key(pub_key, priv_key);

    auto info = tester.get_info();

    std::cout<<info.GetUint64("head_block_num")<<std::endl;
    std::cout<<info.GetString("chain_id")<<std::endl;
    cout<<info.String()<<endl;


    tester.create_account("hello", "helloworld33", pub_key, pub_key, 10*1024*1024, 100000, 1000000);
    tester.produce_block();

    auto account_info = tester.get_account("helloworld33");
    cout<<account_info.GetString("head_block_time")<<endl;

    std::vector<char> buffer;
    buffer.resize(512);
    snprintf(buffer.data(), buffer.size(), "%s/%s", APP_PATH, "hello.wasm");
    string wasm_file(buffer.data());

    snprintf(buffer.data(), buffer.size(), "%s/%s", APP_PATH, "hello.abi");
    string abi_file(buffer.data());

    tester.deploy_contract("helloworld33", wasm_file, abi_file);

    auto permissions = R""""(
    {
        "helloworld33": "active"
    }
    )"""";
    for (int i=0; i<5; i++) {
        tester.push_action("helloworld33", "sayhello", "{}", permissions);
        tester.produce_block();
    }
    REQUIRE( true == true);
}
