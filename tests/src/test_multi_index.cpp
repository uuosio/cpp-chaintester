#include <catch2/catch_test_macros.hpp>
#include <chaintester/chaintester.hpp>
#include <intrinsics.h>
#include "test.h"

extern "C" __attribute__ ((visibility ("default"))) void test_api_multi_index_native_apply( uint64_t receiver, uint64_t code, uint64_t action );

TEST_CASE( "test multi_index", "[multi_index]" ) {
    set_native_apply(test_api_multi_index_native_apply);

    ChainTester t(true);

    auto key = t.create_key();
    auto pub_key = key->get_string("public");
    auto priv_key = key->get_string("private");
    t.import_key(pub_key, priv_key);
    t.create_account("eosio"_n, "testapi"_n, pub_key, pub_key);
    t.enable_debug_contract("testapi"_n, is_coverage_enabled());

    t.deploy_contract("testapi"_n, TEST_API_MULTI_INDEX_WASM, TEST_API_MULTI_INDEX_ABI);

    auto check_failure = [&t]( const string& a, const char* expected_error_msg ) {
        CallFunction(t, "testapi", s2n(a), {}, "eosio_assert_message_exception", expected_error_msg);
    };

    t.push_action( "testapi"_n, "s1g"_n);        // idx64_general
    t.push_action( "testapi"_n, "s1store"_n);    // idx64_store_only
    t.push_action( "testapi"_n, "s1check"_n);    // idx64_check_without_storing
    t.push_action( "testapi"_n, "s2g"_n);        // idx128_general
    t.push_action( "testapi"_n, "s2store"_n);    // idx128_store_only
    t.push_action( "testapi"_n, "s2check"_n);    // idx128_check_without_storing

    t.push_action( "testapi"_n, "s2autoinc"_n);  // idx128_autoincrement_test
    t.push_action( "testapi"_n, "s2autoinc1"_n); // idx128_autoincrement_test_part1
    t.push_action( "testapi"_n, "s2autoinc2"_n); // idx128_autoincrement_test_part2
    t.push_action( "testapi"_n, "s3g"_n);        // idx256_general
    t.push_action( "testapi"_n, "sdg"_n);        // idx_double_general
    t.push_action( "testapi"_n, "sldg"_n);       // idx_long_double_general

    check_failure( "s1pkend", "cannot increment end iterator" ); // idx64_pk_iterator_exceed_end
    check_failure( "s1skend", "cannot increment end iterator" ); // idx64_sk_iterator_exceed_end
    check_failure( "s1pkbegin", "cannot decrement iterator at beginning of table" ); // idx64_pk_iterator_exceed_begin
    check_failure( "s1skbegin", "cannot decrement iterator at beginning of index" ); // idx64_sk_iterator_exceed_begin
    check_failure( "s1pkref", "object passed to iterator_to is not in multi_index" ); // idx64_pass_pk_ref_to_other_table
    check_failure( "s1skref", "object passed to iterator_to is not in multi_index" ); // idx64_pass_sk_ref_to_other_table
//    check_failure( "s1pkitrto", "object passed to iterator_to is not in multi_index" ); // idx64_pass_pk_end_itr_to_iterator_to
    check_failure( "s1pkmodify", "cannot pass end iterator to modify" ); // idx64_pass_pk_end_itr_to_modify
    check_failure( "s1pkerase", "cannot pass end iterator to erase" ); // idx64_pass_pk_end_itr_to_erase
//    check_failure( "s1skitrto", "object passed to iterator_to is not in multi_index" ); // idx64_pass_sk_end_itr_to_iterator_to
    check_failure( "s1skmodify", "cannot pass end iterator to modify" ); // idx64_pass_sk_end_itr_to_modify
    check_failure( "s1skerase", "cannot pass end iterator to erase" ); // idx64_pass_sk_end_itr_to_erase
    check_failure( "s1modpk", "updater cannot change primary key when modifying an object" ); // idx64_modify_primary_key
    check_failure( "s1exhaustpk", "next primary key in table is at autoincrement limit" ); // idx64_run_out_of_avl_pk
    check_failure( "s1findfail1", "unable to find key" ); // idx64_require_find_fail
    check_failure( "s1findfail2", "unable to find primary key in require_find" );// idx64_require_find_fail_with_msg
    check_failure( "s1findfail3", "unable to find secondary key" ); // idx64_require_find_sk_fail
    check_failure( "s1findfail4", "unable to find sec key" ); // idx64_require_find_sk_fail_with_msg

    t.push_action( "testapi"_n, "s1skcache"_n); // idx64_sk_cache_pk_lookup
    t.push_action( "testapi"_n, "s1pkcache"_n); // idx64_pk_cache_sk_lookup

}
