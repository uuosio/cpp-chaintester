#pragma once

#include <eosio/eosio.hpp>

#include "jsonobject.h"
#include "chainexception.h"
#include "loader.h"
#include "utils.h"

using namespace eosio;

class IPCChainTester;

class ChainTester {
private:
    std::unique_ptr<IPCChainTester> tester;
private:
    ChainTester (const ChainTester& other) = delete;
    ChainTester (const ChainTester&& other) = delete;
    ChainTester& operator=(const ChainTester&) = delete;
    ChainTester& operator=(ChainTester&& data) = delete;
public:
    ChainTester(bool initialize=true);
    ~ChainTester();

    std::shared_ptr<JsonObject> get_info();

    std::shared_ptr<JsonObject> create_key(const char* key_type="K1");
    void enable_debug_contract(name contract, bool enable);
    bool import_key(const string& pub_key, const string& priv_key);
    std::shared_ptr<JsonObject> create_account(const name creator, const name account, const string& owner_key, const string& active_key, int64_t ram_bytes=10*1024*1024, int64_t stake_net=100000, int64_t stake_cpu=1000000);
    std::shared_ptr<JsonObject> get_account(const name account);
    void produce_block(int64_t next_block_delay_seconds = 0);
    void produce_blocks(int n);

    std::shared_ptr<JsonObject> push_action(const name account, const name action, const vector<char>& arguments, const vector<permission_level>& permissions);
    std::shared_ptr<JsonObject> push_action(const name account, const name action, const vector<char>& arguments, const name signer=name());
    std::shared_ptr<JsonObject> push_action(const name account, const name action, const string& arguments, const name signer=name());
    std::shared_ptr<JsonObject> push_action(const name account, const name action, const string& arguments="", const string& permissions="");

    template<typename T>
    std::shared_ptr<JsonObject> push_action(const name account, const name action, const T&& arguments, const vector<permission_level>& permissions) {
        return this->push_action(account, action, eosio::pack(arguments), permissions);
    }

    template<typename... Ts>
    std::shared_ptr<JsonObject> push_action(const name account, const name action, const std::tuple<Ts...>& arguments, const name signer) {
        return this->push_action(account, action, eosio::pack(arguments), signer);
    }

    std::shared_ptr<JsonObject> push_actions(const std::vector<action>& actions);
    std::shared_ptr<JsonObject> deploy_contract(const name account, const string& wasmFile, const string& abiFile);

//     /*
//         key_type: "i64"|"i128"|"i256"|"float64"|"float128"|"sha256"|"ripemd160"
//         index_position: "2"|"3"|"4"|"5"|"6"|"7"|"8"|"9"|"10"
//     */
    std::shared_ptr<JsonObject> get_table_rows(bool json,
                                    const name code, const name scope, const name table,
                                    const name lower_bound, const name upper_bound,
                                    int64_t limit,
                                    const string& key_type = "",
                                    const string& index_position = "",
                                    bool reverse = false,
                                    bool show_payer = true);
    int64_t get_balance(const name account, const name token_account="eosio.token"_n, const string& symbol="EOS");
    optional<int64_t> get_balance_ex(const name account, const name token_account, const string& symbol);
};

std::string hex_str(const uint8_t *data, int len);
