#include <map>
#include <chaintester/loader.h>

using namespace eosio;
std::map<uint64_t, fn_apply> g_apply_map;

fn_apply g_apply = nullptr;

void set_native_apply(name contract, fn_apply fn) {
    g_apply_map[contract.value] = fn;
}

fn_apply get_native_apply(name contract) {
    auto it = g_apply_map.find(contract.value);
    if (it == g_apply_map.end()) {
        return nullptr;
    }
    return g_apply;
}

bool call_native_apply(uint64_t receiver, uint64_t first_receiver, uint64_t action) {
    auto apply = get_native_apply(name(receiver));
    if (apply) {
        apply(receiver, first_receiver, action);
        return true;
    }
    return false;
}
