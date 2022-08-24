#pragma once

#include <iostream>
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

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
// using namespace ::apache::thrift::server;

using namespace ::server;

using namespace  ::chaintester;
using namespace ::rapidjson;
using namespace ::std;

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

    const string& GetString() {
        return *static_cast<string*>(value);
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


class JsonObject {
private:
    Document d;
private:
    JsonObject (const JsonObject& other);
    JsonObject (const JsonObject&& other);
    JsonObject& operator=(const JsonObject&);
public:
    JsonObject(const string& s) {
        d.Parse(s.c_str());
    }

    JsonObject(const char* s) {
        d.Parse(s);
    }

    template<typename... Ts>
    Value GetValue(Ts... args) {
        const int size = sizeof...(args);
        JsonKey _args[size] = {args...};
        Value v;
        for (int i=0; i<size; i++) {
            auto key = &_args[i];
            if (key->GetType() == KeyType::String) {
                v = d[key->GetString().c_str()];
            }
        }
        return v;
    }

    template<typename... Ts>
    string GetString(Ts... args) {
        auto v = GetValue(args...);
        return v.GetString();
    }

    template<typename... Ts>
    uint64_t GetUint64(Ts... args) {
        auto v = GetValue(args...);
        return v.GetUint64();
    }

    string String() {
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        d.Accept(writer);
        return string(buffer.GetString(), buffer.GetLength());
    }
};

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

    std::shared_ptr<JsonObject> push_action(const string& account, const string& action, const string& arguments, const string& permissions);
    std::shared_ptr<JsonObject> deploy_contract(const string& account, const string& wasmFile, const string& abiFile);
};

std::shared_ptr<ApplyClient> GetApplyClient();

typedef void (*fn_apply)(uint64_t receiver, uint64_t first_receiver, uint64_t action);
void SetApplyFn(fn_apply fn);
fn_apply GetApplyFn();
