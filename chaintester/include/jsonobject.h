#pragma once

#include <iostream>
#include <vector>
#include <variant>
#include <optional>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace ::rapidjson;
using namespace ::std;

using JsonKey = std::variant<string, int>;

class JsonObject: public Document {
private:
    string raw;
private:
    JsonObject (const JsonObject& other);
    JsonObject (const JsonObject&& other);
    JsonObject& operator=(const JsonObject& o);

public:
    JsonObject(const string& s) {
        raw = s;
        this->Parse(s.c_str());
    }

    JsonObject(const char* s) {
        raw = string(s);
        this->Parse(s);
    }

    template<typename... Ts>
    Value& get_value(Ts... args) {
        if (!this->has_value(args...)) {
            throw std::runtime_error("value does not exists!");
        }

        const int size = sizeof...(args);
        JsonKey _args[size] = {args...};

        auto& key = _args[0];
        Value* v = this;
        for (int i=0; i<size; i++) {
            auto& key = _args[i];
            if (const string* _key = std::get_if<string>(&key)) {
                v = &(*v)[_key->c_str()];
            } else if (const int* _key = std::get_if<int>(&key)) {
                v = &(*v)[*_key];
            }
        }
        return *v;
    }

    template<typename... Ts>
    bool has_value(Ts... args) {
        const int size = sizeof...(args);
        JsonKey _args[size] = {args...};
        Value* v = this;
        for (int i=0; i<size; i++) {
            auto& key = _args[i];
            if (const string* _key = std::get_if<string>(&key)) {
                if (v->HasMember(_key->c_str())) {
                    v = &(*v)[_key->c_str()];
                } else {
                    return false;
                }
            } else if (const int* _key = std::get_if<int>(&key)) {
                if (!v->IsArray()) {
                    return false;
                }
                if (*_key >= v->Size()) {
                    return false;
                }
                v = &(*v)[*_key];
            }
        }
        return true;
    }

    template<typename... Ts>
    string get_string(Ts... args) {
        Value& v = get_value(args...);
        if (v.IsString()) {
            return v.GetString();
        } else {
            StringBuffer buffer;
            Writer<StringBuffer> writer(buffer);
            v.Accept(writer);
            return std::string(buffer.GetString(), buffer.GetLength());
        }
    }

    template<typename... Ts>
    uint64_t get_uint64(Ts... args) {
        auto& v = get_value(args...);
        return v.GetUint64();
    }

    const string& to_string() const {
        return raw;
        // StringBuffer buffer;
        // Writer<StringBuffer> writer(buffer);
        // this->Accept(writer);
        // return std::string(buffer.GetString(), buffer.GetLength());
    }
};

static inline string JsonToString(Value& value) {
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    value.Accept(writer);
    return string(buffer.GetString(), buffer.GetLength());
}
