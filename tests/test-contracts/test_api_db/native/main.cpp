#include "test_api_db.hpp"

extern "C" {
   __attribute__ ((visibility ("default"))) void test_api_db_native_apply( uint64_t receiver, uint64_t code, uint64_t action ) {
        size_t size = eosio::action_data_size();
        std::vector<char> data;
        data.resize(size);
        eosio::read_action_data(data.data(), size);
        eosio::datastream<const char*> ds(data.data(), data.size());

        test_api_db test(eosio::name(receiver), eosio::name(code), ds);
        if (receiver != code) {
            return;
        }
        switch (action) {
            case "pg"_n.value: {
                test.primary_i64_general();
                break;
            }
//    [[eosio::action("pl")]]
//    void primary_i64_lowerbound();
            case "pl"_n.value: {
                test.primary_i64_lowerbound();
                break;
            }
//    [[eosio::action("pu")]]
//    void primary_i64_upperbound();
            case "pu"_n.value: {
                test.primary_i64_upperbound();
                break;
            }
//    [[eosio::action("s1g")]]
//    void idx64_general();
            case "s1g"_n.value: {
                test.idx64_general();
                break;
            }
//    [[eosio::action("s1l")]]
//    void idx64_lowerbound();
            case "s1l"_n.value: {
                test.idx64_lowerbound();
                break;
            }
//    [[eosio::action("s1u")]]
//    void idx64_upperbound();
            case "s1u"_n.value: {
                test.idx64_upperbound();
                break;
            }
//    [[eosio::action("tia")]]
//    void test_invalid_access( eosio::name code, uint64_t val, uint32_t index, bool store );
            // case "tia"_n.value: {
            //     test.test_invalid_access();
            // }
//    [[eosio::action("sdnancreate")]]
//    void idx_double_nan_create_fail();
            case "sdnancreate"_n.value: {
                test.idx_double_nan_create_fail();
                break;
            }
//    [[eosio::action("sdnanmodify")]]
//    void idx_double_nan_modify_fail();
            case "sdnanmodify"_n.value: {
                test.idx_double_nan_modify_fail();
                break;
            }
//    [[eosio::action("sdnanlookup")]]
//    void idx_double_nan_lookup_fail( uint32_t lookup_type );
            // case "sdnanlookup"_n.value: {
            //     test.idx_double_nan_lookup_fail();
            // }
//    [[eosio::action("sk32align")]]
//    void misaligned_secondary_key256_tests();
            case "sk32align"_n.value: {
                test.misaligned_secondary_key256_tests();
                break;
            }
        }
   }
}

