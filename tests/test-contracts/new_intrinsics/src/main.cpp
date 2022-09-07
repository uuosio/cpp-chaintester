#include <new_intrinsics.hpp>

extern "C" __attribute__ ((visibility ("default"))) void new_intrinsics_native_apply( uint64_t receiver, uint64_t code, uint64_t action ) {
   if (code == receiver) {
      switch(action) {
         case "test"_n.value:
            eosio::execute_action( eosio::name(receiver), eosio::name(code), &hello::test );
            break;
      }
   }
}
