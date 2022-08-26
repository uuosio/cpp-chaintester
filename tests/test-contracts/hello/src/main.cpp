#include <hello.hpp>

#define EOSIO_DISPATCH_NATIVE( TYPE, MEMBERS ) \
extern "C" { \
   __attribute__ ((visibility ("default"))) void hello_native_apply( uint64_t receiver, uint64_t code, uint64_t action ) { \
      if( code == receiver ) { \
         switch( action ) { \
            EOSIO_DISPATCH_HELPER( TYPE, MEMBERS ) \
         } \
         /* does not allow destructor of thiscontract to run: eosio_exit(0); */ \
      } \
   } \
}

EOSIO_DISPATCH_NATIVE(hello, (hi)(check))
