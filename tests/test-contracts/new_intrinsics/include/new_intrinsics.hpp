#include <eosio/eosio.hpp>
using namespace eosio;

class [[eosio::contract]] hello : public contract {
   public:
      using contract::contract;

      [[eosio::action]]
      void test(uint32_t block_num);

      using test_action = action_wrapper<"test"_n, &hello::test>;
};
