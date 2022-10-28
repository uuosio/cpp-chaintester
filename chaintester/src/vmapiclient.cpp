#include <stdexcept>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

// #include <chaintester/loader.h>
#include <chaintester/utils.hpp>

#include "gen/IPCChainTester.h"
#include "gen/Apply.h"
#include "gen/ApplyRequest.h"

#include "TSimpleServer.h"

#include "vmapiclient.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

VMAPIClient::VMAPIClient() {
    std::shared_ptr<TTransport> socket(new TSocket("127.0.0.1", 9092));
    std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    transport->open();
    client = new ApplyClient(protocol);
}

VMAPIClient* VMAPIClient::get_instance() {
    if (!_instance) {
        _instance = new VMAPIClient();
    }
    return _instance;
}

ApplyClient* VMAPIClient::operator->() const {
    if (!in_apply) {
        throw std::runtime_error("error: call vm api function out of apply context!");
    }
    return client;
}

bool VMAPIClient::is_in_apply() {
    return in_apply;
}

VMAPIClient* VMAPIClient::_instance = nullptr;

bool call_native_apply(uint64_t receiver, uint64_t first_receiver, uint64_t action);
void VMAPIClient::on_apply(uint64_t receiver, uint64_t first_receiver, uint64_t action) {
    in_apply = true;
    try {
        call_native_apply(receiver, first_receiver, action);
        client->end_apply();
    } catch (apache::thrift::TException ex) {
        printf("+++++++exception on apply(%s, %s, %s):%s\n", n2s(receiver).c_str(), n2s(first_receiver).c_str(), n2s(action).c_str(), ex.what());
        client->end_apply();
    }
    in_apply = false;
}
