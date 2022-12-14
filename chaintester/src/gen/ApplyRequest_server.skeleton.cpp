// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "ApplyRequest.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace  ::chaintester;

class ApplyRequestHandler : virtual public ApplyRequestIf {
 public:
  ApplyRequestHandler() {
    // Your initialization goes here
  }

  int32_t apply_request(const Uint64& receiver, const Uint64& firstReceiver, const Uint64& action, const int32_t chainTesterId) {
    // Your implementation goes here
    printf("apply_request\n");
  }

  int32_t apply_end(const int32_t chainTesterId) {
    // Your implementation goes here
    printf("apply_end\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  ::std::shared_ptr<ApplyRequestHandler> handler(new ApplyRequestHandler());
  ::std::shared_ptr<TProcessor> processor(new ApplyRequestProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

