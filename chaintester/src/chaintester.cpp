#include <fstream>
#include <iterator>
#include <vector>

#include <iomanip>
#include <sstream>
#include <string>

#include <chrono>
#include <thread>

#include "chaintester.h"

static std::shared_ptr<ApplyClient> gApplyClient;

std::shared_ptr<ApplyClient> GetApplyClient() {
    if (!gApplyClient) {
        std::shared_ptr<TTransport> socket(new TSocket("127.0.0.1", 9092));
        std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
        transport->open();
        gApplyClient = std::shared_ptr<ApplyClient>(new ApplyClient(protocol));
    }
    return gApplyClient;
}


class ApplyRequestHandler : virtual public ApplyRequestIf {
 public:
  ApplyRequestHandler() {
    // Your initialization goes here
  }

  int32_t apply_request(const Uint64& receiver, const Uint64& firstReceiver, const Uint64& action) {
    GetApplyClient()->prints("hello, c++\n");
    GetApplyClient()->end_apply();
    return 1;
  }

  int32_t apply_end() {
    return 0;
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

    void push_action(std::string& _return, const int32_t id, const std::string& account, const std::string& action, const std::string& arguments, const std::string& permissions)
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
};

static std::shared_ptr<ChainTesterClient> gChainTesterClient;

std::shared_ptr<ChainTesterClient> GetChainTesterClient() {
    if (!gChainTesterClient) {
        std::shared_ptr<TTransport> socket(new TSocket("127.0.0.1", 9090));
        std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
        transport->open();
        gChainTesterClient = std::shared_ptr<ChainTesterClient>(new ChainTesterClient(protocol));
        gChainTesterClient->init_vm_api();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        GetApplyClient();
        gChainTesterClient->init_apply_request();
        GetApplyRequestServer()->wait_for_connection();
    }
    return gChainTesterClient;
}

ChainTester::ChainTester(bool initialize) {
    client = GetChainTesterClient();
    id = client->new_chain(initialize);
}

ChainTester::~ChainTester() {
    client->free_chain(id);
}

JsonObject ChainTester::get_info() {
    string info;
    client->get_info(info, id);
    return JsonObject(info);
}

JsonObject ChainTester::create_key(const char* key_type) {
    string key;
    client->create_key(key, key_type);
    return JsonObject(key);
}

void ChainTester::enable_debug_contract(const char* contract, bool enable) {
    client->enable_debug_contract(id, contract, enable);
}

bool ChainTester::import_key(const string& pub_key, const string& priv_key) {
    return client->import_key(id, pub_key, priv_key);    
}

JsonObject ChainTester::create_account(const string& creator, const string& account, const string& owner_key, const string& active_key, int64_t ram_bytes, int64_t stake_net, int64_t stake_cpu) {
    string ret;
    client->create_account(ret, id, creator, account, owner_key, active_key, ram_bytes, stake_net, stake_cpu);
    return JsonObject(ret);
}

JsonObject ChainTester::get_account(const string& account) {
    string ret;
    client->get_account(ret, id, account);
    return JsonObject(ret);
}

void ChainTester::produce_block(int64_t next_block_delay_seconds) {
    client->produce_block(id, next_block_delay_seconds);
}

JsonObject ChainTester::push_action(const string& account, const string& action, const string& arguments, const string& permissions) {
    string ret;
    client->push_action(ret, id, account, action, arguments, permissions);
    return JsonObject(ret);
}

std::string hex_str(const uint8_t *data, int len)
{
     std::stringstream ss;
     ss << std::hex;

     for( int i(0) ; i < len; ++i )
         ss << std::setw(2) << std::setfill('0') << (int)data[i];

     return ss.str();
}

JsonObject ChainTester::deploy_contract(const string& account, const string& wasmFile, const string& abiFile) {
    string ret;
    std::ifstream wasm(wasmFile, std::ios::binary);
    std::ifstream abi(abiFile, std::ios::binary);

    std::vector<uint8_t> wasm_data(std::istreambuf_iterator<char>(wasm), {});
    std::vector<uint8_t> abi_data(std::istreambuf_iterator<char>(abi), {});

    auto hex_wasm_data = hex_str(wasm_data.data(), wasm_data.size());
    auto str_abi_data = string((char *)abi_data.data(), abi_data.size());
    client->deploy_contract(ret, id, account, hex_wasm_data, str_abi_data);
    return JsonObject(ret);
}
