#include <new_intrinsics.hpp>
#include <eosio/system.hpp>
#include <eosio/action.h>

[[eosio::action]]
void hello::test(uint32_t block_num) {
   eosio::check(block_num == eosio::current_block_number(), "bad block number");
   eosio::print_f("%", (uint32_t)eosio::current_block_number());
   set_action_return_value((void *)"helloworld", 10);
}
