#pragma once
#include <stdint.h>

namespace chaintester {
    class ApplyClient;
}

using namespace chaintester;

class VMAPIClient {
private:
    VMAPIClient();

public:
    bool is_in_apply();
    void on_apply(uint64_t receiver, uint64_t first_receiver, uint64_t action);
    static VMAPIClient* get_instance();
    ApplyClient* operator->() const;

private:
    bool in_apply = false;
    ApplyClient* client;
    static VMAPIClient* _instance;
};

VMAPIClient& GetApplyClient();
