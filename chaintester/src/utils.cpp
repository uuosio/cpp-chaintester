#include <iomanip>
#include <sstream>
#include <stdint.h>
#include <string>
#include <eosio/name.hpp>
#include <iostream>
#include <vector>

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
        epoch = int64_t(timegm(&_tm)) * 1000;
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

//modified from https://gist.github.com/arnobaer/973c91a7e8b5088087e20257df3c82d3
std::vector<uint8_t> hex2bytes(const std::string& s)
{
    size_t size = s.size()/2*2;
    std::vector<uint8_t> v;
    v.reserve(size/2);
    for (auto i = 0; i < size; i += 2)
    {
        std::string slice(s.c_str()+i, 2);
        uint8_t value = (uint8_t)std::stoul(slice, 0, 16);
        v.push_back(value);
    }
    return v;
}
