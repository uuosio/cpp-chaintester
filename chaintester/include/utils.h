#pragma once
#include <string>

using namespace std;
std::string n2s(uint64_t n);
uint64_t s2n(const string& s);
int64_t str2ms(const string& iso_time);
std::vector<char> hex2bytes(const std::string& s);