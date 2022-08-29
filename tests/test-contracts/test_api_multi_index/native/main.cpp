#include "test_api_multi_index.hpp"
extern "C" {
   __attribute__ ((visibility ("default"))) void test_api_multi_index_native_apply( uint64_t receiver, uint64_t code, uint64_t action ) {
        size_t size = eosio::action_data_size();
        std::vector<char> data;
        data.resize(size);
        eosio::read_action_data(data.data(), size);
        eosio::datastream<const char*> ds(data.data(), data.size());

        test_api_multi_index test(eosio::name(receiver), eosio::name(code), ds);
        if (receiver != code) {
            return;
        }
        switch (action) {
//    [[eosio::action("s1g")]]
//    void idx64_general();
            case "s1g"_n.value: {
                test.idx64_general();
                break;
            }
//    [[eosio::action("s1store")]]
//    void idx64_store_only();
            case "s1store"_n.value: {
                test.idx64_store_only();
                break;
            }
//    [[eosio::action("s1check")]]
//    void idx64_check_without_storing();
            case "s1check"_n.value: {
                test.idx64_check_without_storing();
                break;
            }
//    [[eosio::action("s1findfail1")]]
//    void idx64_require_find_fail();
            case "s1findfail1"_n.value: {
                test.idx64_require_find_fail();
                break;
            }
//    [[eosio::action("s1findfail2")]]
//    void idx64_require_find_fail_with_msg();
            case "s1findfail2"_n.value: {
                test.idx64_require_find_fail_with_msg();
                break;
            }
//    [[eosio::action("s1findfail3")]]
//    void idx64_require_find_sk_fail();
            case "s1findfail3"_n.value: {
                test.idx64_require_find_sk_fail();
                break;
            }
//    [[eosio::action("s1findfail4")]]
//    void idx64_require_find_sk_fail_with_msg();
            case "s1findfail4"_n.value: {
                test.idx64_require_find_sk_fail_with_msg();
                break;
            }
//    [[eosio::action("s1pkend")]]
//    void idx64_pk_iterator_exceed_end();
            case "s1pkend"_n.value: {
                test.idx64_pk_iterator_exceed_end();
                break;
            }
//    [[eosio::action("s1skend")]]
//    void idx64_sk_iterator_exceed_end();
            case "s1skend"_n.value: {
                test.idx64_sk_iterator_exceed_end();
                break;
            }
//    [[eosio::action("s1pkbegin")]]
//    void idx64_pk_iterator_exceed_begin();
            case "s1pkbegin"_n.value: {
                test.idx64_pk_iterator_exceed_begin();
                break;
            }
//    [[eosio::action("s1skbegin")]]
//    void idx64_sk_iterator_exceed_begin();
            case "s1skbegin"_n.value: {
                test.idx64_sk_iterator_exceed_begin();
                break;
            }
//    [[eosio::action("s1pkref")]]
//    void idx64_pass_pk_ref_to_other_table();
            case "s1pkref"_n.value: {
                test.idx64_pass_pk_ref_to_other_table();
                break;
            }
//    [[eosio::action("s1skref")]]
//    void idx64_pass_sk_ref_to_other_table();
            case "s1skref"_n.value: {
                test.idx64_pass_sk_ref_to_other_table();
                break;
            }
//    [[eosio::action("s1pkitrto")]]
//    void idx64_pass_pk_end_itr_to_iterator_to();
            case "s1pkitrto"_n.value: {
                test.idx64_pass_pk_end_itr_to_iterator_to();
                break;
            }
//    [[eosio::action("s1pkmodify")]]
//    void idx64_pass_pk_end_itr_to_modify();
            case "s1pkmodify"_n.value: {
                test.idx64_pass_pk_end_itr_to_modify();
                break;
            }
//    [[eosio::action("s1pkerase")]]
//    void idx64_pass_pk_end_itr_to_erase();
            case "s1pkerase"_n.value: {
                test.idx64_pass_pk_end_itr_to_erase();
                break;
            }
//    [[eosio::action("s1skitrto")]]
//    void idx64_pass_sk_end_itr_to_iterator_to();
            case "s1skitrto"_n.value: {
                test.idx64_pass_sk_end_itr_to_iterator_to();
                break;
            }
//    [[eosio::action("s1skmodify")]]
//    void idx64_pass_sk_end_itr_to_modify();
            case "s1skmodify"_n.value: {
                test.idx64_pass_sk_end_itr_to_modify();
                break;
            }
//    [[eosio::action("s1skerase")]]
//    void idx64_pass_sk_end_itr_to_erase();
            case "s1skerase"_n.value: {
                test.idx64_pass_sk_end_itr_to_erase();
                break;
            }
//    [[eosio::action("s1modpk")]]
//    void idx64_modify_primary_key();
            case "s1modpk"_n.value: {
                test.idx64_modify_primary_key();
                break;
            }
//    [[eosio::action("s1exhaustpk")]]
//    void idx64_run_out_of_avl_pk();
            case "s1exhaustpk"_n.value: {
                test.idx64_run_out_of_avl_pk();
                break;
            }
//    [[eosio::action("s1skcache")]]
//    void idx64_sk_cache_pk_lookup();
            case "s1skcache"_n.value: {
                test.idx64_sk_cache_pk_lookup();
                break;
            }
//    [[eosio::action("s1pkcache")]]
//    void idx64_pk_cache_sk_lookup();
            case "s1pkcache"_n.value: {
                test.idx64_pk_cache_sk_lookup();
                break;
            }
//    [[eosio::action("s2g")]]
//    void idx128_general();
            case "s2g"_n.value: {
                test.idx128_general();
                break;
            }
//    [[eosio::action("s2store")]]
//    void idx128_store_only();
            case "s2store"_n.value: {
                test.idx128_store_only();
                break;
            }
//    [[eosio::action("s2check")]]
//    void idx128_check_without_storing();
            case "s2check"_n.value: {
                test.idx128_check_without_storing();
                break;
            }
//    [[eosio::action("s2autoinc")]]
//    void idx128_autoincrement_test();
            case "s2autoinc"_n.value: {
                test.idx128_autoincrement_test();
                break;
            }
//    [[eosio::action("s2autoinc1")]]
//    void idx128_autoincrement_test_part1();
            case "s2autoinc1"_n.value: {
                test.idx128_autoincrement_test_part1();
                break;
            }
//    [[eosio::action("s2autoinc2")]]
//    void idx128_autoincrement_test_part2();
            case "s2autoinc2"_n.value: {
                test.idx128_autoincrement_test_part2();
                break;
            }
//    [[eosio::action("s3g")]]
//    void idx256_general();
            case "s3g"_n.value: {
                test.idx256_general();
                break;
            }
//    [[eosio::action("sdg")]]
//    void idx_double_general();
            case "sdg"_n.value: {
                test.idx_double_general();
                break;
            }
//    [[eosio::action("sldg")]]
//    void idx_long_double_general();
            case "sldg"_n.value: {
                test.idx_long_double_general();
                break;
            }
        }
   }
}

