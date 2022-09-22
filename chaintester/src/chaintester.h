#pragma once

#include <iostream>
#include <vector>
#include <variant>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


#include "loader.h"
#include "utils.h"

using namespace ::rapidjson;
using namespace ::std;

namespace chaintester {
    class IPCChainTesterClient;
    class ApplyClient;
}

using namespace chaintester;

using ActionArguments = std::variant<string, vector<char>>;
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
            throw std::runtime_error("value did not exists!");
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

class chain_exception: public std::exception {
private:
    JsonObject o;
private:
    chain_exception& operator = (const chain_exception& ex) noexcept;
public:
    chain_exception(const string& s) noexcept : std::exception(), o(s) {
    }

    chain_exception (const chain_exception& ex) noexcept: o(ex.value().to_string()) {
    }

    const JsonObject& value() const {
        return o;
    }

    ~chain_exception() {

    }

    const char* what() const noexcept {
        return o.to_string().c_str();
    }
};

struct TxAction {
  std::string account;
  std::string action;
  ActionArguments arguments;
  std::string permissions;
};

class ChainTester {
private:
    std::shared_ptr<IPCChainTesterClient> client;
    int32_t id;
private:
    ChainTester (const ChainTester& other);
    ChainTester (const ChainTester&& other);
    ChainTester& operator=(const ChainTester&);
    ChainTester& operator=(ChainTester&& data);
public:
    ChainTester(bool initialize=true);
    ~ChainTester();

    std::shared_ptr<JsonObject> get_info();

    std::shared_ptr<JsonObject> create_key(const char* key_type="K1");
    void enable_debug_contract(const char* contract, bool enable);
    bool import_key(const string& pub_key, const string& priv_key);
    std::shared_ptr<JsonObject> create_account(const string& creator, const string& account, const string& owner_key, const string& active_key, int64_t ram_bytes=10*1024*1024, int64_t stake_net=100000, int64_t stake_cpu=1000000);
    std::shared_ptr<JsonObject> get_account(const string& account);
    void produce_block(int64_t next_block_delay_seconds = 0);

    std::shared_ptr<JsonObject> push_action(const string& account, const string& action, const ActionArguments& arguments="", const string& permissions="");
    std::shared_ptr<JsonObject> push_actions(const std::vector<TxAction> & actions);
    std::shared_ptr<JsonObject> deploy_contract(const string& account, const string& wasmFile, const string& abiFile);

    /*
        key_type: "i64"|"i128"|"i256"|"float64"|"float128"|"sha256"|"ripemd160"
        index_position: "2"|"3"|"4"|"5"|"6"|"7"|"8"|"9"|"10"
    */
    std::shared_ptr<JsonObject> get_table_rows(bool json,
                                    const string& code, const string& scope, const string& table,
                                    const string& lower_bound, const string& upper_bound,
                                    int64_t limit,
                                    const string& key_type = "",
                                    const string& index_position = "",
                                    bool reverse = false,
                                    bool show_payer = true);
    uint64_t get_balance(const string& account, const string& token_account="eosio.token", const string& symbol="EOS");
};

std::string hex_str(const uint8_t *data, int len);

std::shared_ptr<ApplyClient> GetApplyClient();
bool IsInApply();
