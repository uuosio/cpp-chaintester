#pragma once
#include <algorithm> 
#include <cctype>
#include <locale>
#include <string>
#include <vector>

using namespace std;

std::string n2s(uint64_t n);
uint64_t s2n(const string& s);
int64_t str2ms(const string& iso_time);
std::vector<char> hex2bytes(const std::string& s);
std::string hex_str(const uint8_t *data, int len);


//https://stackoverflow.com/questions/216823/how-to-trim-an-stdstring

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

