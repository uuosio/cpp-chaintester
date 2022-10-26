#include "ipcchaintester.hpp"
#include <chaintester/chaintester.hpp>

ChainTester::ChainTester(bool initialize) {
    tester = std::make_unique<IPCChainTester>(initialize);
}

ChainTester::~ChainTester() {
}

std::shared_ptr<JsonObject> ChainTester::get_info() {
    return tester->get_info();
}

std::shared_ptr<JsonObject> ChainTester::create_key(const char* key_type) {
    return tester->create_key(key_type);
}

void ChainTester::enable_debug_contract(name contract, bool enable) {
    tester->enable_debug_contract(contract.to_string().c_str(), enable);
}

bool ChainTester::import_key(const string& pub_key, const string& priv_key) {
    return tester->import_key(pub_key, priv_key);    
}

std::shared_ptr<JsonObject> ChainTester::create_account(const name creator, const name account, const string& owner_key, const string& active_key, int64_t ram_bytes, int64_t stake_net, int64_t stake_cpu) {
    return tester->create_account(creator.to_string(), account.to_string(), owner_key, active_key, ram_bytes, stake_net, stake_cpu);
}

std::shared_ptr<JsonObject> ChainTester::get_account(const name account) {
    return tester->get_account(account.to_string());
}

void ChainTester::produce_block(int64_t next_block_delay_seconds) {
    tester->produce_block(next_block_delay_seconds);
}

void ChainTester::produce_blocks(int n) {
    for (int i=0; i<n; i++) {
        tester->produce_block();
    }
}

static string permissions_to_json_string(const vector<permission_level>& permissions) {
    string _permissions = "{";
    for (int i=0; i<permissions.size(); i++) {
        char buf[128];
        auto& perm = permissions[i];
        int n = snprintf(buf, sizeof(buf), R"("%s": "%s")", perm.actor.to_string().c_str(), perm.permission.to_string().c_str());
        _permissions += string(buf, n);
        if (i + 1 < permissions.size()) {
            _permissions += ",";
        }
    }
    _permissions += "}";
    return _permissions;
}

std::shared_ptr<JsonObject> ChainTester::push_action_ex(const name account, const name action, const vector<char>& arguments, const vector<permission_level>& permissions) {
    return tester->push_action(account.to_string(), action.to_string(), arguments, permissions_to_json_string(permissions));
}

std::shared_ptr<JsonObject> ChainTester::push_action_ex(const name account, const name action, const vector<char>& arguments, const name signer) {
    name _signer = signer;
    if (signer == name()) {
        _signer = account;
    }
    return tester->push_action(account.to_string(), action.to_string(), arguments, std::vector<Permission>({std::make_pair(_signer.to_string(), string("active"))}));
}

std::shared_ptr<JsonObject> ChainTester::push_action_ex(const name account, const name action, const string& arguments, const name signer) {
    name _signer = signer;
    if (signer == name()) {
        _signer = account;
    }
    return tester->push_action(account.to_string(), action.to_string(), arguments, std::vector<Permission>({std::make_pair(_signer.to_string(), string("active"))}));
}

std::shared_ptr<JsonObject> ChainTester::push_action_ex(const name account, const name action, const string& arguments, const string& permissions) {
    return tester->push_action(account.to_string(), action.to_string(), arguments, permissions);
}

std::shared_ptr<JsonObject> ChainTester::push_actions(const std::vector<action>& actions) {
    vector<TxAction> aa;
    for (auto& a : actions) {
        TxAction _a;
        _a.account = a.account.to_string();
        _a.action = a.name.to_string();
        _a.arguments = a.data;
        _a.permissions = permissions_to_json_string(a.authorization);
        aa.emplace_back(_a);
    }
    return tester->push_actions(aa);
}

std::shared_ptr<JsonObject> ChainTester::deploy_contract(const name account, const string& wasmFile, const string& abiFile) {
    return tester->deploy_contract(account.to_string(), wasmFile, abiFile);
}

ActionSender ChainTester::new_action(name account, name action, name signer) {
    return ActionSender(*this, account, action, signer);
}

ActionSender ChainTester::new_action_sender() {
    return ActionSender(*this);
}

std::shared_ptr<JsonObject> ChainTester::get_table_rows(bool json,
                                const name code, const name scope, const name table,
                                const name lower_bound, const name upper_bound,
                                int64_t limit,
                                const string& key_type,
                                const string& index_position,
                                bool reverse,
                                bool show_payer) {
    return tester->get_table_rows(json, code.to_string(), scope.to_string(), table.to_string(),
                                        lower_bound.to_string(), upper_bound.to_string(),
                                        limit,
                                        key_type,
                                        index_position,
                                        reverse,
                                        show_payer
    );
}

int64_t ChainTester::get_balance(const name account, const name token_account, const string& symbol) {
    return tester->get_balance(account.to_string(), token_account.to_string(), symbol);
}

optional<int64_t> ChainTester::get_balance_ex(const name account, const name token_account, const string& symbol) {
    return tester->get_balance_ex(account.to_string(), token_account.to_string(), symbol);
}

ActionSender::ActionSender(ChainTester& tester, name account, name action, const name signer):
    tester(tester),
    account(account),
    action(action),
    permissions({{signer, "active"_n}})
{
}

ActionSender::ActionSender(ChainTester& tester, name account, name action, const vector<permission_level>& permissions): 
    tester(tester),
    account(account),
    action(action),
    permissions(permissions)
{

}

ActionSender::ActionSender(ChainTester& tester):
    tester(tester)
{

}

// ActionSender::ActionSender(const ActionSender& other):
//     tester(other.tester),
//     account(other.account),
//     action(other.action),
//     permissions(other.permissions)
// {
// }

ActionSender::~ActionSender() {

}
