#pragma once

#include "jsonobject.h"
#include "loader.h"
#include "utils.h"


namespace chaintester {
    class IPCChainTesterClient;
    class ApplyClient;
}

using namespace chaintester;

using ActionArguments = std::variant<string, vector<char>>;

using Permission = std::pair<string, string>;
using Permissions = std::variant<string, vector<Permission>>;

struct TxAction {
  std::string account;
  std::string action;
  ActionArguments arguments;
  Permissions permissions;
};

class IPCChainTester {
private:
    std::shared_ptr<IPCChainTesterClient> client;
    int32_t id;
private:
    IPCChainTester (const IPCChainTester& other);
    IPCChainTester (const IPCChainTester&& other);
    IPCChainTester& operator=(const IPCChainTester&);
    IPCChainTester& operator=(IPCChainTester&& data);
public:
    IPCChainTester(bool initialize=true);
    ~IPCChainTester();

    std::shared_ptr<JsonObject> get_info();

    std::shared_ptr<JsonObject> create_key(const char* key_type="K1");
    void enable_debug_contract(const char* contract, bool enable);
    bool import_key(const string& pub_key, const string& priv_key);
    std::shared_ptr<JsonObject> create_account(const string& creator, const string& account, const string& owner_key, const string& active_key, int64_t ram_bytes=10*1024*1024, int64_t stake_net=100000, int64_t stake_cpu=1000000);
    std::shared_ptr<JsonObject> get_account(const string& account);
    void produce_block(int64_t next_block_delay_seconds = 0);
    void produce_blocks(int n);

    std::shared_ptr<JsonObject> push_action(const string& account, const string& action, const ActionArguments& arguments="", const Permissions& permissions="");
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
    int64_t get_balance(const string& account, const string& token_account="eosio.token", const string& symbol="EOS");
    optional<int64_t> get_balance_ex(const string& account, const string& token_account, const string& symbol);
};

std::string hex_str(const uint8_t *data, int len);
