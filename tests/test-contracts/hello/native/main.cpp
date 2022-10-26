#include <hello.hpp>

extern "C" __attribute__ ((visibility ("default"))) void hello_native_apply( uint64_t receiver, uint64_t code, uint64_t action ) {
   if (code == receiver) {
      switch(action) {
         case "hi"_n.value:
            eosio::execute_action( eosio::name(receiver), eosio::name(code), &hello::hi );
            break;
         case "check"_n.value:
            eosio::execute_action( eosio::name(receiver), eosio::name(code), &hello::check );
            break;
      }
   }
}
