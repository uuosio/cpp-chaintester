#include "chaintester.h"

int main(int argc, char **argv) {
    ChainTester tester;
    cout<<tester.get_info()<<endl;

//   std::shared_ptr<TTransport> socket(new TSocket("127.0.0.1", 9090));
//   std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
//   std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
//   IPCChainTesterClient client(protocol);

//   try {
//     transport->open();

//     int32_t id = client.new_chain();

//     string info;
//     client.get_info(info, id);
//     cout<<info<<endl;

//     client.free_chain(id);

//     transport->close();
    
//   } catch (TException& tx) {
//     cout << "ERROR: " << tx.what() << endl;
//   }
}