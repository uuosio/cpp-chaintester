#include <fstream>
#include <iterator>
#include <vector>

#include <iomanip>
#include <sstream>
#include <string>

#include "chaintester.h"

static std::shared_ptr<IPCChainTesterClient> gChainTesterClient;

std::shared_ptr<IPCChainTesterClient> GetChainTesterClient() {
    if (!gChainTesterClient) {
        std::shared_ptr<TTransport> socket(new TSocket("127.0.0.1", 9090));
        std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
        transport->open();
        gChainTesterClient = std::shared_ptr<IPCChainTesterClient>(new IPCChainTesterClient(protocol));
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
