#include "chaintester.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <catch2/catch_test_macros.hpp>

#include "test.h"

#include <sstream>

string I64Str(int64_t i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}

string U64Str(uint64_t i) {
    std::stringstream ss;
    ss << i;
    return ss.str();
}

typedef unsigned __int128 uint128_t;

//reference from https://stackoverflow.com/questions/11656241/how-to-print-uint128-t-number-using-gcc
string U128Str(uint128_t n) {
    static char buf[40];
    unsigned int i, j, m = 39;
    memset(buf, 0, 40);
    for (i = 128; i-- > 0;) {
        int carry = !!(n & ((uint128_t)1 << i));
        for (j = 39; j-- > m + 1 || carry;) {
            int d = 2 * buf[j] + carry;
            carry = d > 9;
            buf[j] = carry ? d - 10 : d;
        }
        m = j;
    }
    for (i = 0; i < 38; i++) {
        if (buf[i]) {
            break;
        }
    }
    for (j = i; j < 39; j++) {
        buf[j] += '0';
    }
    return string(buf + i);
}

static void apply(uint64_t receiver, uint64_t first_receiver, uint64_t action) {
    GetApplyClient()->prints("hello, c++\n");
}

TEST_CASE( "test chaintester", "[chaintester]" ) {
    ChainTester tester(true);
    set_apply(apply);

    // tester.enable_debug_contract("hello", true);
    tester.enable_debug_contract("helloworld33", true);

    auto key = tester.create_key();
    std::cout<<key->to_string()<<std::endl;

    auto pub_key = key->get_string("public");
    auto priv_key = key->get_string("private");
    tester.import_key(pub_key, priv_key);

    auto info = tester.get_info();

    std::cout<<info->get_uint64("head_block_num")<<std::endl;
    std::cout<<info->get_string("chain_id")<<std::endl;
    cout<<info->to_string()<<endl;

    tester.create_account("hello", "helloworld33", pub_key, pub_key, 10*1024*1024, 100000, 1000000);
    tester.produce_block();

    auto account_info = tester.get_account("helloworld33");
    cout<<account_info->get_string("head_block_time")<<endl;

    tester.deploy_contract("helloworld33", HELLO_WASM, HELLO_ABI);

    auto args = R""""(
    {
        "nm": "alice"
    }
    )"""";

    auto permissions = R""""(
    {
        "helloworld33": "active"
    }
    )"""";
    for (int i=0; i<5; i++) {
        tester.push_action("helloworld33", "hi", args, permissions);
        tester.produce_block();
    }
}
