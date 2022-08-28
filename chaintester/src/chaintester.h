#pragma once

#include <iostream>
#include <vector>
#include <variant>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "gen/IPCChainTester.h"
#include "gen/Apply.h"
#include "gen/ApplyRequest.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "TSimpleServer.h"

#include "loader.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
// using namespace ::apache::thrift::server;

using namespace ::server;

using namespace  ::chaintester;
using namespace ::rapidjson;
using namespace ::std;

using ActionArguments = std::variant<string, vector<char>>;

enum KeyType {
    Unknown,
    String,
    Int,
};


class JsonKey {
public:
    KeyType key_type;
private:
    void *value;
private:
    JsonKey (const JsonKey& other);
    // JsonKey (JsonKey&& other);
    JsonKey& operator=(const JsonKey&);
public:
    JsonKey (JsonKey&& other) {
        this->key_type = other.key_type;
        this->value = other.value;
        other.key_type = KeyType::Unknown;
        other.value = nullptr;
    }

    JsonKey() {
        key_type = KeyType::Unknown;
    }

    JsonKey(int n) {
        key_type = KeyType::Int;
        value = new int(n);
    }

    JsonKey(const char* s) {
        key_type = KeyType::String;
        value = new string(s);
    }

    KeyType GetType() {
        return key_type;
    }

    const string& get_string() {
        return *static_cast<string*>(value);
    }

    int get_int() {
        return *static_cast<int*>(value);
    }

    ~JsonKey() {
        if (key_type == KeyType::String) {
            delete (string*)value;
        } else if (key_type == KeyType::Int) {
            delete (int*)value;
        }
    }

    JsonKey& operator=(const string& key) {
        this->key_type = KeyType::String;
        this->value = new string(key);
        return *this;
    }

    JsonKey& operator=(const char* key) {
        this->key_type = KeyType::String;
        this->value = new string(key);
        return *this;
    }

    JsonKey& operator=(int key) {
        this->key_type = KeyType::Int;
        this->value = new int(key);
        return *this;
    }
};


class JsonObject: public Document {
private:
    JsonObject (const JsonObject& other);
    JsonObject (const JsonObject&& other);
    JsonObject& operator=(const JsonObject&);
public:
    JsonObject(const string& s) {
        this->Parse(s.c_str());
    }

    JsonObject(const char* s) {
        this->Parse(s);
    }

    template<typename... Ts>
    Value& get_value(Ts... args) {
        const int size = sizeof...(args);
        JsonKey _args[size] = {args...};

        auto key = &_args[0];
        Value* v = this;
        for (int i=0; i<size; i++) {
            auto key = &_args[i];
            if (key->GetType() == KeyType::String) {
                v = &(*v)[key->get_string().c_str()];
            } else if (key->GetType() == KeyType::Int) {
                v = &(*v)[key->get_int()];
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
            auto key = &_args[i];
            if (key->GetType() == KeyType::String) {
                string _key = key->get_string();
                if (v->HasMember(_key.c_str())) {
                    v = &(*v)[_key.c_str()];
                } else {
                    return false;
                }
            } else if (key->GetType() == KeyType::Int) {
                int _key = key->get_int();
                if (!v->IsArray()) {
                    return false;
                }
                if (_key >= v->Size()) {
                    return false;
                }
                v = &(*v)[_key];
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

    string to_string() {
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        this->Accept(writer);
        return std::string(buffer.GetString(), buffer.GetLength());
    }
};

static inline string JsonToString(Value& value) {
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    value.Accept(writer);
    return string(buffer.GetString(), buffer.GetLength());
}

class ChainTester {
private:
    std::shared_ptr<IPCChainTesterClient> client;
    int32_t id;
private:
    ChainTester (const ChainTester& other);
    ChainTester (const ChainTester&& other);
    ChainTester& operator=(const ChainTester&);
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

    std::shared_ptr<JsonObject> push_action(const string& account, const string& action, const ActionArguments& arguments, const string& permissions);
    std::shared_ptr<JsonObject> deploy_contract(const string& account, const string& wasmFile, const string& abiFile);
};

std::string hex_str(const uint8_t *data, int len);

std::shared_ptr<ApplyClient> GetApplyClient();
