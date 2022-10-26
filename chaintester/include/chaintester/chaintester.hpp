#pragma once

#include <tuple>
#include <exception>

#include <eosio/eosio.hpp>
#include <chaintester/chainexception.hpp>
#include <catch2/catch_test_macros.hpp>

#include "jsonobject.hpp"
#include "loader.h"
#include "utils.hpp"

using namespace eosio;

class IPCChainTester;
class ActionSender;

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

    template<typename T>
    std::shared_ptr<JsonObject> push_action(const name account, const name action, const T& arguments, const vector<permission_level>& permissions) {
        return this->push_action_ex(account, action, eosio::pack(arguments), permissions);
    }

    template<typename T>
    std::shared_ptr<JsonObject> push_action(const name account, const name action, const T& arguments, const name signer) {
        return this->push_action_ex(account, action, eosio::pack(arguments), signer);
    }

    std::shared_ptr<JsonObject> push_actions(const std::vector<action>& actions);
    std::shared_ptr<JsonObject> deploy_contract(const name account, const string& wasmFile, const string& abiFile);

    ActionSender new_action(name account, name action, name signer);
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

    //deprecated, do not use it
    //push action with raw arguments 
    std::shared_ptr<JsonObject> push_action_ex(const name account, const name action, const vector<char>& arguments, const vector<permission_level>& permissions);
    std::shared_ptr<JsonObject> push_action_ex(const name account, const name action, const vector<char>& arguments, const name signer=name());

    //push action with json string arguments
    std::shared_ptr<JsonObject> push_action_ex(const name account, const name action, const string& arguments, const name signer=name());
    std::shared_ptr<JsonObject> push_action_ex(const name account, const name action, const string& arguments="", const string& permissions="");

    std::shared_ptr<JsonObject> push_action(const name account, const name action) {
        return this->push_action_ex(account, action, "", name());
    }

};

class ActionSender {
private:
    ActionSender (const ActionSender&& other) = delete;
    ActionSender& operator=(const ActionSender&) = delete;
    ActionSender& operator=(ActionSender&& o) = delete;
    ActionSender (const ActionSender& other) = delete;

private:
    ActionSender(ChainTester& tester, name account, name action, const name signer=name());
    ActionSender(ChainTester& tester, name account, name action, const vector<permission_level>& permissions);

public:
    ~ActionSender();

    template<typename... Ts>
    std::shared_ptr<JsonObject> send(Ts... args) {
        return tester.push_action_ex(account, action, eosio::pack(std::make_tuple(args...)), permissions);
    }

    template<typename... Ts>
    ChainException send_and_catch_exception(Ts... args) {
        try {
            tester.push_action_ex(account, action, eosio::pack(std::make_tuple(args...)), permissions);
            throw std::runtime_error("send_require_assertion: should throw exception");
        } catch(ChainException& ex) {
            return ex;
        }
    }

    std::shared_ptr<JsonObject> send_raw(vector<char>& raw_args) {
        return tester.push_action_ex(account, action, raw_args, permissions);
    }

private:
    name account;
    name action;
    vector<permission_level> permissions;
    ChainTester& tester;

friend class ChainTester;
};