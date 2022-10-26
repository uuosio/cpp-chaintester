#pragma once
#include <string>
#include <vector>

using namespace std;
std::string n2s(uint64_t n);
uint64_t s2n(const string& s);
int64_t str2ms(const string& iso_time);
std::vector<char> hex2bytes(const std::string& s);
std::string hex_str(const uint8_t *data, int len);
