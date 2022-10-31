#include <hello.hpp>
[[eosio::action]]
void hello::hi( name nm ) {
   print_f("Name : %\n", nm);
}

[[eosio::action]]
void hello::check( name nm ) {
   print_f("Name : %\n", nm);
   eosio::check(nm == "hello"_n, "check name not equal to `hello`");
}

[[eosio::action("sum")]] 
void hello::sum(uint64_t a, uint64_t b) {
   print_f("sum: %\n", a + b);
}
