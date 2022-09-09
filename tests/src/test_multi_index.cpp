#include <catch2/catch_test_macros.hpp>
#include <chaintester.h>
#include <intrinsics.h>
#include "test.h"

extern "C" __attribute__ ((visibility ("default"))) void test_api_multi_index_native_apply( uint64_t receiver, uint64_t code, uint64_t action );

TEST_CASE( "test multi_index", "[multi_index]" ) {
    set_apply(test_api_multi_index_native_apply);

    ChainTester t(true);

    auto key = t.create_key();
    auto pub_key = key->get_string("public");
    auto priv_key = key->get_string("private");
    t.import_key(pub_key, priv_key);
    t.create_account("eosio", "testapi", pub_key, pub_key);
    t.enable_debug_contract("testapi", true);

    t.deploy_contract("testapi", HELLO_WASM, HELLO_ABI);

    auto check_failure = [&t]( const string& a, const char* expected_error_msg ) {
        CallFunction(t, "testapi", s2n(a), {}, "eosio_assert_message_exception", expected_error_msg);
    };

    t.push_action( "testapi", "s1g");        // idx64_general
    t.push_action( "testapi", "s1store");    // idx64_store_only
    t.push_action( "testapi", "s1check");    // idx64_check_without_storing
    t.push_action( "testapi", "s2g");        // idx128_general
    t.push_action( "testapi", "s2store");    // idx128_store_only
    t.push_action( "testapi", "s2check");    // idx128_check_without_storing
    t.push_action( "testapi", "s2autoinc");  // idx128_autoincrement_test
    t.push_action( "testapi", "s2autoinc1"); // idx128_autoincrement_test_part1
    t.push_action( "testapi", "s2autoinc2"); // idx128_autoincrement_test_part2
    t.push_action( "testapi", "s3g");        // idx256_general
    t.push_action( "testapi", "sdg");        // idx_double_general
    t.push_action( "testapi", "sldg");       // idx_long_double_general

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

    t.push_action( "testapi", "s1skcache"); // idx64_sk_cache_pk_lookup
    t.push_action( "testapi", "s1pkcache"); // idx64_pk_cache_sk_lookup

}
