#pragma once

#include <iostream>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "gen/IPCChainTester.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace  ::chaintester;
using  namespace ::std;

class ChainTester {
private:
    std::shared_ptr<IPCChainTesterClient> client;
    int32_t id;
public:
    ChainTester();
    ~ChainTester();

    string get_info();
};
