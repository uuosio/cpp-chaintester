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
    // set_apply(apply);

    // tester.enable_debug_contract("hello", true);
    // tester.enable_debug_contract("helloworld33", true);

    auto key = tester.create_key();
    std::cout<<key->to_string()<<std::endl;

    auto pub_key = key->get_string("public");
    auto priv_key = key->get_string("private");
    tester.import_key(pub_key, priv_key);

    auto info = tester.get_info();

    WARN(info->get_uint64("head_block_num"));
    WARN(info->get_string("chain_id"));
    WARN(info->to_string());

    auto ret = tester.create_account("hello", "helloworld33", pub_key, pub_key, 10*1024*1024, 100000, 1000000);
    tester.produce_block();

    auto account_info = tester.get_account("helloworld33");
    WARN(account_info->get_string("head_block_time"));
    
    ret = tester.deploy_contract("helloworld33", TEST_MULTI_INDEX_EXAMPLE_WASM, TEST_MULTI_INDEX_EXAMPLE_ABI);
    WARN(ret->to_string());

    auto args = R""""(
    {
        "user": "alice"
    }
    )"""";

    auto permissions = R""""(
    {
        "helloworld33": "active"
    }
    )"""";
    
    ret = tester.push_action("helloworld33", "set", args, permissions);
    WARN(ret->to_string());

    /*
        key_type: "i64"|"i128"|"i256"|"float64"|"float128"|"sha256"|"ripemd160"
        index_position: "2"|"3"|"4"|"5"|"6"|"7"|"8"|"9"|"10"
    */
    ret = tester.get_table_rows(true, "helloworld33", "helloworld33", "testtaba", "alice", "alice", 10);
    WARN(ret->to_string());

    ret = tester.get_table_rows(true, "helloworld33", "helloworld33", "testtaba", "second", "second", 10, "i64", "2");
    WARN(ret->to_string());
}
