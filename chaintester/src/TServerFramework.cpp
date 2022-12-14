/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <algorithm>
#include <stdexcept>
#include <stdint.h>
#include "TServerFramework.h"

namespace server {

using apache::thrift::concurrency::Synchronized;
using apache::thrift::protocol::TProtocol;
using apache::thrift::protocol::TProtocolFactory;
using std::bind;
using std::shared_ptr;
using apache::thrift::transport::TServerTransport;
using apache::thrift::transport::TTransport;
using apache::thrift::transport::TTransportException;
using apache::thrift::transport::TTransportFactory;
using std::string;

TServerFramework::TServerFramework(const shared_ptr<TProcessorFactory>& processorFactory,
                                   const shared_ptr<TServerTransport>& serverTransport,
                                   const shared_ptr<TTransportFactory>& transportFactory,
                                   const shared_ptr<TProtocolFactory>& protocolFactory)
  : TServer(processorFactory, serverTransport, transportFactory, protocolFactory),
    clients_(0),
    hwm_(0),
    limit_(INT64_MAX) {
}

TServerFramework::TServerFramework(const shared_ptr<TProcessor>& processor,
                                   const shared_ptr<TServerTransport>& serverTransport,
                                   const shared_ptr<TTransportFactory>& transportFactory,
                                   const shared_ptr<TProtocolFactory>& protocolFactory)
  : TServer(processor, serverTransport, transportFactory, protocolFactory),
    clients_(0),
    hwm_(0),
    limit_(INT64_MAX) {
}

TServerFramework::TServerFramework(const shared_ptr<TProcessorFactory>& processorFactory,
                                   const shared_ptr<TServerTransport>& serverTransport,
                                   const shared_ptr<TTransportFactory>& inputTransportFactory,
                                   const shared_ptr<TTransportFactory>& outputTransportFactory,
                                   const shared_ptr<TProtocolFactory>& inputProtocolFactory,
                                   const shared_ptr<TProtocolFactory>& outputProtocolFactory)
  : TServer(processorFactory,
            serverTransport,
            inputTransportFactory,
            outputTransportFactory,
            inputProtocolFactory,
            outputProtocolFactory),
    clients_(0),
    hwm_(0),
    limit_(INT64_MAX) {
}

TServerFramework::TServerFramework(const shared_ptr<TProcessor>& processor,
                                   const shared_ptr<TServerTransport>& serverTransport,
                                   const shared_ptr<TTransportFactory>& inputTransportFactory,
                                   const shared_ptr<TTransportFactory>& outputTransportFactory,
                                   const shared_ptr<TProtocolFactory>& inputProtocolFactory,
                                   const shared_ptr<TProtocolFactory>& outputProtocolFactory)
  : TServer(processor,
            serverTransport,
            inputTransportFactory,
            outputTransportFactory,
            inputProtocolFactory,
            outputProtocolFactory),
    clients_(0),
    hwm_(0),
    limit_(INT64_MAX) {
}

TServerFramework::~TServerFramework() = default;

template <typename T>
static void releaseOneDescriptor(const string& name, T& pTransport) {
  if (pTransport) {
    try {
      pTransport->close();
    } catch (const TTransportException& ttx) {
      string errStr = string("TServerFramework " + name + " close failed: ") + ttx.what();
      apache::thrift::GlobalOutput(errStr.c_str());
    }
  }
}

void TServerFramework::prepare() {

  // Start the server listening
  serverTransport_->listen();

  // Run the preServe event to indicate server is now listening
  // and that it is safe to connect.
  if (eventHandler_) {
    eventHandler_->preServe();
  }
}

void TServerFramework::wait_for_connection() {
  // If we have reached the limit on the number of concurrent
  // clients allowed, wait for one or more clients to drain before
  // accepting another.
  {
    Synchronized sync(mon_);
    while (clients_ >= limit_) {
      mon_.wait();
    }
  }

  client = serverTransport_->accept();

  inputTransport = inputTransportFactory_->getTransport(client);
  outputTransport = outputTransportFactory_->getTransport(client);
  if (!outputProtocolFactory_) {
    inputProtocol = inputProtocolFactory_->getProtocol(inputTransport, outputTransport);
    outputProtocol = inputProtocol;
  } else {
    inputProtocol = inputProtocolFactory_->getProtocol(inputTransport);
    outputProtocol = outputProtocolFactory_->getProtocol(outputTransport);
  }
  conn = std::shared_ptr<TConnectedClient>(new TConnectedClient(getProcessor(inputProtocol, outputProtocol, client),
                              inputProtocol,
                              outputProtocol,
                              eventHandler_,
                              client));

}

void TServerFramework::serve_once() {
  // Fetch client from server
  do {
    try {
      conn->run();
    } catch (TTransportException& ttx) {
      releaseOneDescriptor("inputTransport", inputTransport);
      releaseOneDescriptor("outputTransport", outputTransport);
      releaseOneDescriptor("client", client);
      if (ttx.getType() == TTransportException::TIMED_OUT
          || ttx.getType() == TTransportException::CLIENT_DISCONNECT) {
        // Accept timeout and client disconnect - continue processing.
        continue;
      } else if (ttx.getType() == TTransportException::END_OF_FILE
                 || ttx.getType() == TTransportException::INTERRUPTED) {
        // Server was interrupted.  This only happens when stopping.
        break;
      } else {
        // All other transport exceptions are logged.
        // State of connection is unknown.  Done.
        string errStr = string("TServerTransport died: ") + ttx.what();
        apache::thrift::GlobalOutput(errStr.c_str());
        break;
      }
    }
  } while(false);

  // releaseOneDescriptor("serverTransport", serverTransport_);
}

void TServerFramework::serve() {
}

int64_t TServerFramework::getConcurrentClientLimit() const {
  Synchronized sync(mon_);
  return limit_;
}

int64_t TServerFramework::getConcurrentClientCount() const {
  Synchronized sync(mon_);
  return clients_;
}

int64_t TServerFramework::getConcurrentClientCountHWM() const {
  Synchronized sync(mon_);
  return hwm_;
}

void TServerFramework::setConcurrentClientLimit(int64_t newLimit) {
  if (newLimit < 1) {
    throw std::invalid_argument("newLimit must be greater than zero");
  }
  Synchronized sync(mon_);
  limit_ = newLimit;
  if (limit_ - clients_ > 0) {
    mon_.notify();
  }
}

void TServerFramework::stop() {
  // Order is important because serve() releases serverTransport_ when it is
  // interrupted, which closes the socket that interruptChildren uses.
  serverTransport_->interruptChildren();
  serverTransport_->interrupt();
}

void TServerFramework::newlyConnectedClient(const shared_ptr<TConnectedClient>& pClient) {
  {
    Synchronized sync(mon_);
    ++clients_;
    hwm_ = (std::max)(hwm_, clients_);
  }

  onClientConnected(pClient);
}

void TServerFramework::disposeConnectedClient(TConnectedClient* pClient) {
  onClientDisconnected(pClient);
  delete pClient;

  Synchronized sync(mon_);
  if (limit_ - --clients_ > 0) {
    mon_.notify();
  }
}

} // server
