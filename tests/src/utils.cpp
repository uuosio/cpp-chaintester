#include <stdint.h>
#include <string>
#include <eosio/name.hpp>

using namespace std;
using namespace eosio;

std::string n2s(uint64_t n) {
    name _n(n);
    char buffer[13];
    auto end = _n.write_as_string(buffer, buffer + sizeof(buffer) );
    return {buffer, end};
}

uint64_t s2n(const string& s) {
    name n(s);
    return n.value;
}

