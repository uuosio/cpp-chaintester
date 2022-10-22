#include <fstream>
#include <iterator>
#include <vector>

#include <iomanip>
#include <sstream>
#include <string>
#include <tuple>

#include <chrono>
#include <thread>
#include <memory>
#include <mutex>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "gen/IPCChainTester.h"
#include "gen/Apply.h"
#include "gen/ApplyRequest.h"

#include "TSimpleServer.h"

#include "vmapiclient.h"
#include "ipcchaintester.h"
#include "chainexception.h"


using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
// using namespace ::apache::thrift::server;

using namespace ::server;
using namespace ::chaintester;

std::mutex g_apply_mutex;

void InitApplyClient() {
    VMAPIClient::get_instance();
}

VMAPIClient& GetApplyClient() {
    return *VMAPIClient::get_instance();
}

class ApplyRequestHandler : virtual public ApplyRequestIf {
 public:
  ApplyRequestHandler() {
    // Your initialization goes here
  }

  int32_t apply_request(const Uint64& receiver, const Uint64& first_receiver, const Uint64& action) {
    uint64_t _receiver;
    uint64_t _first_receiver;
    uint64_t _action;
    memcpy(&_receiver, receiver.rawValue.c_str(), 8);
    memcpy(&_first_receiver, first_receiver.rawValue.c_str(), 8);
    memcpy(&_action, action.rawValue.c_str(), 8);

    std::lock_guard<std::mutex> guard(g_apply_mutex);

    GetApplyClient().on_apply(_receiver, _first_receiver, _action);
    return 1;
  }

  int32_t apply_end() {
    return 1;
  }
};

class ApplyRequestServer: public TSimpleServer {
public:
  ApplyRequestServer(
      const std::shared_ptr<apache::thrift::TProcessor>& processor,
      const std::shared_ptr<apache::thrift::transport::TServerTransport>& serverTransport,
      const std::shared_ptr<apache::thrift::transport::TTransportFactory>& transportFactory,
      const std::shared_ptr<apache::thrift::protocol::TProtocolFactory>& protocolFactory) :TSimpleServer(
            processor,
            serverTransport,
            transportFactory,
            protocolFactory
      ) {
        prepare();
      }
};

static std::shared_ptr<ApplyRequestServer> gApplyRequestServer;

std::shared_ptr<TSimpleServer> GetApplyRequestServer() {
    int port = 9091;
    ::std::shared_ptr<ApplyRequestHandler> handler(new ApplyRequestHandler());
    ::std::shared_ptr<TProcessor> processor(new ApplyRequestProcessor(handler));
    ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
    if (!gApplyRequestServer) {
        gApplyRequestServer = std::shared_ptr<ApplyRequestServer>(new ApplyRequestServer(processor, serverTransport, transportFactory, protocolFactory));
    }
    return gApplyRequestServer;
//   TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
//   server.serve();
//   return 0;
}

class ChainTesterClient: public IPCChainTesterClient {
 public:
    ChainTesterClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot): IPCChainTesterClient(prot) {
    }

    ChainTesterClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot): IPCChainTesterClient(iprot, oprot) {
    }

    void push_action(std::string& _return, const int32_t id, const std::string& account, const std::string& action, const ActionArguments& arguments, const std::string& permissions)
    {
        send_push_action(id, account, action, arguments, permissions);
        GetApplyRequestServer()->serve_once();
        recv_push_action(_return);
    }

    void push_actions(std::string& _return, const int32_t id, const std::vector<Action> & actions)
    {
        send_push_actions(id, actions);
        GetApplyRequestServer()->serve_once();
        recv_push_actions(_return);
    }

    void produce_block(const int32_t id, const int64_t next_block_skip_seconds)
    {
        send_produce_block(id, next_block_skip_seconds);
        GetApplyRequestServer()->serve_once();
        recv_produce_block();
    }
};

static std::shared_ptr<ChainTesterClient> gChainTesterClient;

void init_intrinsics_func();

std::shared_ptr<ChainTesterClient> GetChainTesterClient() {
    if (!gChainTesterClient) {
        init_intrinsics_func();
        std::shared_ptr<TTransport> socket(new TSocket("127.0.0.1", 9090));
        std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
        transport->open();
        gChainTesterClient = std::shared_ptr<ChainTesterClient>(new ChainTesterClient(protocol));

        gChainTesterClient->init_vm_api();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        InitApplyClient();

        gChainTesterClient->init_apply_request();
        GetApplyRequestServer()->wait_for_connection();
    }
    return gChainTesterClient;
}

IPCChainTester::IPCChainTester(bool initialize) {
    client = GetChainTesterClient();
    id = client->new_chain(initialize);
}

IPCChainTester::~IPCChainTester() {
    client->free_chain(id);
}

std::shared_ptr<JsonObject> IPCChainTester::get_info() {
    string info;
    client->get_info(info, id);
    return std::make_shared<JsonObject>(info);
}

std::shared_ptr<JsonObject> IPCChainTester::create_key(const char* key_type) {
    string key;
    client->create_key(key, key_type);
    return std::make_shared<JsonObject>(key);
}

void IPCChainTester::enable_debug_contract(const char* contract, bool enable) {
    client->enable_debug_contract(id, contract, enable);
}

bool IPCChainTester::import_key(const string& pub_key, const string& priv_key) {
    return client->import_key(id, pub_key, priv_key);    
}

std::shared_ptr<JsonObject> IPCChainTester::create_account(const string& creator, const string& account, const string& owner_key, const string& active_key, int64_t ram_bytes, int64_t stake_net, int64_t stake_cpu) {
    string ret;
    client->create_account(ret, id, creator, account, owner_key, active_key, ram_bytes, stake_net, stake_cpu);
    return std::make_shared<JsonObject>(ret);
}

std::shared_ptr<JsonObject> IPCChainTester::get_account(const string& account) {
    string ret;
    client->get_account(ret, id, account);
    return std::make_shared<JsonObject>(ret);
}

void IPCChainTester::produce_block(int64_t next_block_delay_seconds) {
    client->produce_block(id, next_block_delay_seconds);
}

void IPCChainTester::produce_blocks(int n) {
    for (int i=0; i<n; i++) {
        this->produce_block();
    }
}

string permissions_to_json_string(const vector<Permission>& v) {
    string _permissions = "{";
    for (int i=0; i<v.size(); i++) {
        char buf[128];
        auto& perm = v[i];
        int n = snprintf(buf, sizeof(buf), R"("%s": "%s")", perm.first.c_str(), perm.second.c_str());
        _permissions += string(buf, n);
        if (i + 1 < v.size()) {
            _permissions += ",";
        }
    }
    _permissions += "}";
    return _permissions;
}

string permissions_to_json_string(const Permissions& permissions) {
    if(const string* s = std::get_if<string>(&permissions)) {
        return *s;
    } else if (const vector<Permission>* v = std::get_if<vector<Permission>>(&permissions)) {
        return permissions_to_json_string(*v);
    }
    return "";
}

std::shared_ptr<JsonObject> IPCChainTester::push_action(const string& account, const string& action, const TxActionArguments& arguments, const Permissions& permissions) {
    string ret;
    string _permissions;
    ActionArguments _arguments;

    if(const string* s  = std::get_if<string>(&arguments)) {
        _arguments.__set_json_args(*s);
    } else if (const vector<char>* v  = std::get_if<vector<char>>(&arguments)) {
        _arguments.__set_raw_args(string(v->data(), v->size()));
    }

    _permissions = permissions_to_json_string(permissions);

    if (_permissions.size() == 0) {
        char buf[128];
        int n = snprintf(buf, sizeof(buf), R""""({"%s": "active"})"""", account.c_str());
        _permissions = string(buf, n);
    }

    client->push_action(ret, id, account, action, _arguments, _permissions);
    auto _ret = std::make_shared<JsonObject>(ret);
    if (_ret->has_value("except")) {
        throw chain_exception(ret);
    }
    return _ret;
}

std::shared_ptr<JsonObject> IPCChainTester::push_actions(const std::vector<TxAction>& actions) {
    vector<Action> aa;
    for (auto& a : actions) {
        ActionArguments arguments;
        if(const string* s  = std::get_if<string>(&a.arguments)) {
            arguments.__set_json_args(*s);
        } else if (const vector<char>* v  = std::get_if<vector<char>>(&a.arguments)) {
            arguments.__set_raw_args(string(v->data(), v->size()));
        }
        Action _a;
        _a.account = a.account;
        _a.action = a.action;
        _a.arguments = arguments;
        _a.permissions = permissions_to_json_string(a.permissions);
        aa.emplace_back(_a);
    }

    string ret;
    client->push_actions(ret, id, aa);
    auto _ret = std::make_shared<JsonObject>(ret);
    if (_ret->has_value("except")) {
        throw chain_exception(ret);
    }
    return _ret;
}

std::shared_ptr<JsonObject> IPCChainTester::deploy_contract(const string& account, const string& wasmFile, const string& abiFile) {
    string ret;
    std::ifstream wasm(wasmFile, std::ios::binary);
    std::ifstream abi(abiFile, std::ios::binary);

    string hex_wasm_data;
    string str_abi_data;

    if (wasm.is_open()) {
        std::vector<uint8_t> wasm_data(std::istreambuf_iterator<char>(wasm), {});
        hex_wasm_data = hex_str(wasm_data.data(), wasm_data.size());
    } else {
        throw std::runtime_error("wasm file does not exists!");
    }

    if (abi.is_open()) {
        std::vector<uint8_t> abi_data(std::istreambuf_iterator<char>(abi), {});
        str_abi_data = string((char *)abi_data.data(), abi_data.size());
    } else {
        throw std::runtime_error("abi file does not exists!");
    }

    client->deploy_contract(ret, id, account, hex_wasm_data, str_abi_data);
    auto _ret = std::make_shared<JsonObject>(ret);
    if (_ret->has_value("except")) {
        throw chain_exception(ret);
    }
    return _ret;
}

std::shared_ptr<JsonObject> IPCChainTester::get_table_rows(bool json,
                                const string& code, const string& scope, const string& table,
                                const string& lower_bound, const string& upper_bound,
                                int64_t limit,
                                const string& key_type,
                                const string& index_position,
                                bool reverse,
                                bool show_payer) {
    string ret;
    client->get_table_rows(ret, id, json, code, scope, table, lower_bound, upper_bound, limit, key_type, index_position, reverse, show_payer);
    return std::make_shared<JsonObject>(ret);
}

int64_t IPCChainTester::get_balance(const string& account, const string& token_account, const string& symbol) {
    std::shared_ptr<JsonObject> ret = this->get_table_rows(false, token_account, account, "accounts", symbol, "", 1);
    if (!ret->has_value("rows", 0, "data")) {
        return 0;
    }
    string s = ret->get_string("rows", 0, "data");
    auto raw = hex2bytes(s);
    int64_t balance;
    memcpy(&balance, raw.data(), 8);
    return balance;
}

optional<int64_t> IPCChainTester::get_balance_ex(const string& account, const string& token_account, const string& symbol) {
    std::shared_ptr<JsonObject> ret = this->get_table_rows(false, token_account, account, "accounts", symbol, "", 1);
    if (!ret->has_value("rows", 0, "data")) {
        return std::nullopt;
    }
    string s = ret->get_string("rows", 0, "data");
    auto raw = hex2bytes(s);
    int64_t balance;
    memcpy(&balance, raw.data(), 8);
    return balance;
}
