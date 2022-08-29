#include <iomanip>
#include <sstream>
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

int64_t str2ms(const string& iso_time) {
    int64_t epoch;
    std::tm _tm = {};
    std::istringstream ss(iso_time);
    if (ss >> std::get_time(&_tm, "%Y-%m-%dT%H:%M:%S"))
    {
        epoch = int64_t(std::mktime(&_tm)) * 1000;
    }
    auto dot = iso_time.find( '.' );
    if( dot != std::string::npos ) {
        auto ms = iso_time.substr(dot);
        ms[0] = '1';
        while(ms.size() < 4) ms.push_back('0');
        epoch += (std::stoi(ms) - 1000);
    }
    return epoch;
}
