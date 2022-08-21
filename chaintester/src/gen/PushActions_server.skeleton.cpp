// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "PushActions.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace  ::chaintester;

class PushActionsHandler : virtual public PushActionsIf {
 public:
  PushActionsHandler() {
    // Your initialization goes here
  }

  int32_t push_actions(const std::vector<Action> & actions) {
    // Your implementation goes here
    printf("push_actions\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  ::std::shared_ptr<PushActionsHandler> handler(new PushActionsHandler());
  ::std::shared_ptr<TProcessor> processor(new PushActionsProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

