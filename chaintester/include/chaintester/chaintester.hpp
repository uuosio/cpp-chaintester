#pragma once

#include <tuple>
#include <exception>

#include <eosio/eosio.hpp>
#include <chaintester/chainexception.hpp>
#include <catch2/catch_test_macros.hpp>

#include "jsonobject.hpp"
#include "native.h"
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
    bool set_native_contract(name contract, const string& dylib);
    void enable_debugging(bool enable);
    void enable_debug_contract(name contract, bool enable);
    void set_native_apply(name contract, fn_native_apply apply);

    bool import_key(const string& pub_key, const string& priv_key);
    std::shared_ptr<JsonObject> create_account(const name creator, const name account, const string& owner_key, const string& active_key, int64_t ram_bytes=10*1024*1024, int64_t stake_net=100000, int64_t stake_cpu=1000000);
    std::shared_ptr<JsonObject> get_account(const name account);
    void produce_block(int64_t next_block_delay_seconds = 0);
    void produce_blocks(int n);

    template<typename... Ts>
    std::shared_ptr<JsonObject> push_action(const vector<permission_level>& permissions, const name account, const name action, Ts... arguments) {
        return this->push_action_ex(account, action, eosio::pack(arguments...), permissions);
    }

    template<typename... Ts>
    std::shared_ptr<JsonObject> push_action(const name signer, const name account, const name action, Ts... arguments) {
        return this->push_action_ex(account, action, eosio::pack(arguments...), signer);
    }

    std::shared_ptr<JsonObject> push_actions(const std::vector<action>& actions);
    std::shared_ptr<JsonObject> deploy_contract(const name account, const string& wasm_file, const string& abi_file);

    ActionSender new_action_sender();
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
    ActionSender(ChainTester& tester);

public:
    ~ActionSender();

    template<typename... Ts>
    ActionSender& add_action(const name signer, name account, name action, Ts... args) {
        actions.emplace_back(
            eosio::action{
                permission_level{signer, "active"_n},
                account,
                action,
                std::make_tuple(args...)
            }
        );
        return *this;
    }

    template<typename... Ts>
    ActionSender& add_action(const vector<permission_level>& permissions, name account, name action, Ts... args) {
        actions.emplace_back(
            eosio::action{
                permissions,
                account,
                action,
                std::make_tuple(args...)
            }
        );
        return *this;
    }

    std::shared_ptr<JsonObject> send() {
        return tester.push_actions(actions);
    }

    ChainException send_and_catch_exception() {
        try {
            tester.push_actions(actions);
            throw std::runtime_error("send_require_assertion: should throw exception");
        } catch(ChainException& ex) {
            return ex;
        }
    }
private:
    std::vector<eosio::action> actions;
    ChainTester& tester;

friend class ChainTester;
};
