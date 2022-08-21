#include "chaintester.h"

static std::shared_ptr<IPCChainTesterClient> gChainTesterClient;

std::shared_ptr<IPCChainTesterClient> GetChainTesterClient() {
    if (!gChainTesterClient) {
        std::shared_ptr<TTransport> socket(new TSocket("127.0.0.1", 9090));
        std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
        transport->open();
        gChainTesterClient = std::shared_ptr<IPCChainTesterClient>(new IPCChainTesterClient(protocol));
    }
    return gChainTesterClient;
}

ChainTester::ChainTester() {
    client = GetChainTesterClient();
    id = client->new_chain();
}

ChainTester::~ChainTester() {
    client->free_chain(id);
}

string ChainTester::get_info() {
    string info;
    client->get_info(info, id);
    return info;
}

// int main(int argc, char **argv) {

//   try {
    

//     int32_t id = client.new_chain();

//     string info;
//     client.get_info(info, id);
//     cout<<info<<endl;

//     client.free_chain(id);

//     transport->close();
    
//   } catch (TException& tx) {
//     cout << "ERROR: " << tx.what() << endl;
//   }
// }
