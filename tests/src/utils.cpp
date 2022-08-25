#include <stdint.h>
#include <string>

using namespace std;

constexpr uint8_t name_length(uint64_t value) {
    constexpr uint64_t mask = 0xF800000000000000ull;

    if( value == 0 )
    return 0;

    uint8_t l = 0;
    uint8_t i = 0;
    for( auto v = value; i < 13; ++i, v <<= 5 ) {
    if( (v & mask) > 0 ) {
        l = i;
    }
    }

    return l + 1;
}

char* write_as_string(uint64_t value, char* begin, char* end, bool dry_run = false ) {
    static const char* charmap = ".12345abcdefghijklmnopqrstuvwxyz";
    constexpr uint64_t mask = 0xF800000000000000ull;

    if( dry_run || (begin + 13 < begin) || (begin + 13 > end) ) {
    char* actual_end = begin + name_length(value);
    if( dry_run || (actual_end < begin) || (actual_end > end) ) return actual_end;
    }

    auto v = value;
    for( auto i = 0; i < 13; ++i, v <<= 5 ) {
    if( v == 0 ) return begin;

    auto indx = (v & mask) >> (i == 12 ? 60 : 59);
    *begin = charmap[indx];
    ++begin;
    }

    return begin;
}

std::string n2s(uint64_t n) {
    char buffer[13];
    auto end = write_as_string(n, buffer, buffer + sizeof(buffer) );
    return {buffer, end};
}
