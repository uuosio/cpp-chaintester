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
public:
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


class JsonObject: private Document {
private:
    Document d;
public:
    JsonObject(const string& s) {
        d.Parse(s.c_str());
    }

    JsonObject(const char* s) {
        d.Parse(s);
    }

    // string GetString(string& key) {
    //     return d[key.c_str()].GetString();
    // }

    // string GetString(const char* key) {
    //     return d[key].GetString();
    // }

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
public:
    ChainTester(bool initialize=true);
    ~ChainTester();

    JsonObject get_info();

    JsonObject create_key(const char* key_type="K1");
    void enable_debug_contract(const char* contract, bool enable);
    bool import_key(const string& pub_key, const string& priv_key);
    JsonObject create_account(const string& creator, const string& account, const string& owner_key, const string& active_key, int64_t ram_bytes=10*1024*1024, int64_t stake_net=100000, int64_t stake_cpu=1000000);
    JsonObject get_account(const string& account);
    void produce_block(int64_t next_block_delay_seconds = 0);

    JsonObject push_action(const string& account, const string& action, const string& arguments, const string& permissions);
    JsonObject deploy_contract(const string& account, const string& wasmFile, const string& abiFile);
};
