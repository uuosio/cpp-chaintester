#include <stdint.h>
#include <string.h>
#include <assert.h>

#include <string>
#include <vector>

#include <eosio/crypto.hpp>
#include <eosio/datastream.hpp>

using namespace std;

eosio::public_key decode_public_key(const string& str);
