/**
 * Autogenerated by Thrift Compiler (0.15.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "interfaces_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>

namespace chaintester {


TransactionException::~TransactionException() noexcept {
}


void TransactionException::__set_exc(const std::string& val) {
  this->exc = val;
}
std::ostream& operator<<(std::ostream& out, const TransactionException& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t TransactionException::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->exc);
          this->__isset.exc = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t TransactionException::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("TransactionException");

  xfer += oprot->writeFieldBegin("exc", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->exc);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(TransactionException &a, TransactionException &b) {
  using ::std::swap;
  swap(a.exc, b.exc);
  swap(a.__isset, b.__isset);
}

TransactionException::TransactionException(const TransactionException& other0) : TException() {
  exc = other0.exc;
  __isset = other0.__isset;
}
TransactionException& TransactionException::operator=(const TransactionException& other1) {
  exc = other1.exc;
  __isset = other1.__isset;
  return *this;
}
void TransactionException::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "TransactionException(";
  out << "exc=" << to_string(exc);
  out << ")";
}

const char* TransactionException::what() const noexcept {
  try {
    std::stringstream ss;
    ss << "TException - service has thrown: " << *this;
    this->thriftTExceptionMessageHolder_ = ss.str();
    return this->thriftTExceptionMessageHolder_.c_str();
  } catch (const std::exception&) {
    return "TException - service has thrown: TransactionException";
  }
}


AssertException::~AssertException() noexcept {
}


void AssertException::__set_error_message(const std::string& val) {
  this->error_message = val;
}
std::ostream& operator<<(std::ostream& out, const AssertException& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t AssertException::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->error_message);
          this->__isset.error_message = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t AssertException::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("AssertException");

  xfer += oprot->writeFieldBegin("error_message", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->error_message);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(AssertException &a, AssertException &b) {
  using ::std::swap;
  swap(a.error_message, b.error_message);
  swap(a.__isset, b.__isset);
}

AssertException::AssertException(const AssertException& other2) : TException() {
  error_message = other2.error_message;
  __isset = other2.__isset;
}
AssertException& AssertException::operator=(const AssertException& other3) {
  error_message = other3.error_message;
  __isset = other3.__isset;
  return *this;
}
void AssertException::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "AssertException(";
  out << "error_message=" << to_string(error_message);
  out << ")";
}

const char* AssertException::what() const noexcept {
  try {
    std::stringstream ss;
    ss << "TException - service has thrown: " << *this;
    this->thriftTExceptionMessageHolder_ = ss.str();
    return this->thriftTExceptionMessageHolder_.c_str();
  } catch (const std::exception&) {
    return "TException - service has thrown: AssertException";
  }
}


Action::~Action() noexcept {
}


void Action::__set_account(const std::string& val) {
  this->account = val;
}

void Action::__set_action(const std::string& val) {
  this->action = val;
}

void Action::__set_permissions(const std::string& val) {
  this->permissions = val;
}

void Action::__set_arguments(const std::string& val) {
  this->arguments = val;
}
std::ostream& operator<<(std::ostream& out, const Action& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t Action::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->account);
          this->__isset.account = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->action);
          this->__isset.action = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->permissions);
          this->__isset.permissions = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->arguments);
          this->__isset.arguments = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Action::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("Action");

  xfer += oprot->writeFieldBegin("account", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->account);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("action", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->action);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("permissions", ::apache::thrift::protocol::T_STRING, 3);
  xfer += oprot->writeString(this->permissions);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("arguments", ::apache::thrift::protocol::T_STRING, 4);
  xfer += oprot->writeString(this->arguments);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Action &a, Action &b) {
  using ::std::swap;
  swap(a.account, b.account);
  swap(a.action, b.action);
  swap(a.permissions, b.permissions);
  swap(a.arguments, b.arguments);
  swap(a.__isset, b.__isset);
}

Action::Action(const Action& other4) {
  account = other4.account;
  action = other4.action;
  permissions = other4.permissions;
  arguments = other4.arguments;
  __isset = other4.__isset;
}
Action& Action::operator=(const Action& other5) {
  account = other5.account;
  action = other5.action;
  permissions = other5.permissions;
  arguments = other5.arguments;
  __isset = other5.__isset;
  return *this;
}
void Action::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "Action(";
  out << "account=" << to_string(account);
  out << ", " << "action=" << to_string(action);
  out << ", " << "permissions=" << to_string(permissions);
  out << ", " << "arguments=" << to_string(arguments);
  out << ")";
}


Uint64::~Uint64() noexcept {
}


void Uint64::__set_rawValue(const std::string& val) {
  this->rawValue = val;
}
std::ostream& operator<<(std::ostream& out, const Uint64& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t Uint64::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->rawValue);
          this->__isset.rawValue = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Uint64::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("Uint64");

  xfer += oprot->writeFieldBegin("rawValue", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeBinary(this->rawValue);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Uint64 &a, Uint64 &b) {
  using ::std::swap;
  swap(a.rawValue, b.rawValue);
  swap(a.__isset, b.__isset);
}

Uint64::Uint64(const Uint64& other6) {
  rawValue = other6.rawValue;
  __isset = other6.__isset;
}
Uint64& Uint64::operator=(const Uint64& other7) {
  rawValue = other7.rawValue;
  __isset = other7.__isset;
  return *this;
}
void Uint64::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "Uint64(";
  out << "rawValue=" << to_string(rawValue);
  out << ")";
}


DataBuffer::~DataBuffer() noexcept {
}


void DataBuffer::__set_size(const int32_t val) {
  this->size = val;
}

void DataBuffer::__set_buffer(const std::string& val) {
  this->buffer = val;
}
std::ostream& operator<<(std::ostream& out, const DataBuffer& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t DataBuffer::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->size);
          this->__isset.size = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->buffer);
          this->__isset.buffer = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t DataBuffer::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("DataBuffer");

  xfer += oprot->writeFieldBegin("size", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->size);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("buffer", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeBinary(this->buffer);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(DataBuffer &a, DataBuffer &b) {
  using ::std::swap;
  swap(a.size, b.size);
  swap(a.buffer, b.buffer);
  swap(a.__isset, b.__isset);
}

DataBuffer::DataBuffer(const DataBuffer& other8) {
  size = other8.size;
  buffer = other8.buffer;
  __isset = other8.__isset;
}
DataBuffer& DataBuffer::operator=(const DataBuffer& other9) {
  size = other9.size;
  buffer = other9.buffer;
  __isset = other9.__isset;
  return *this;
}
void DataBuffer::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "DataBuffer(";
  out << "size=" << to_string(size);
  out << ", " << "buffer=" << to_string(buffer);
  out << ")";
}


NextPreviousReturn::~NextPreviousReturn() noexcept {
}


void NextPreviousReturn::__set_iterator(const int32_t val) {
  this->iterator = val;
}

void NextPreviousReturn::__set_primary(const Uint64& val) {
  this->primary = val;
}
std::ostream& operator<<(std::ostream& out, const NextPreviousReturn& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t NextPreviousReturn::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->iterator);
          this->__isset.iterator = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->primary.read(iprot);
          this->__isset.primary = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t NextPreviousReturn::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("NextPreviousReturn");

  xfer += oprot->writeFieldBegin("iterator", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->iterator);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("primary", ::apache::thrift::protocol::T_STRUCT, 2);
  xfer += this->primary.write(oprot);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(NextPreviousReturn &a, NextPreviousReturn &b) {
  using ::std::swap;
  swap(a.iterator, b.iterator);
  swap(a.primary, b.primary);
  swap(a.__isset, b.__isset);
}

NextPreviousReturn::NextPreviousReturn(const NextPreviousReturn& other10) {
  iterator = other10.iterator;
  primary = other10.primary;
  __isset = other10.__isset;
}
NextPreviousReturn& NextPreviousReturn::operator=(const NextPreviousReturn& other11) {
  iterator = other11.iterator;
  primary = other11.primary;
  __isset = other11.__isset;
  return *this;
}
void NextPreviousReturn::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "NextPreviousReturn(";
  out << "iterator=" << to_string(iterator);
  out << ", " << "primary=" << to_string(primary);
  out << ")";
}


IteratorPrimaryReturn::~IteratorPrimaryReturn() noexcept {
}


void IteratorPrimaryReturn::__set_iterator(const int32_t val) {
  this->iterator = val;
}

void IteratorPrimaryReturn::__set_primary(const Uint64& val) {
  this->primary = val;
}
std::ostream& operator<<(std::ostream& out, const IteratorPrimaryReturn& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t IteratorPrimaryReturn::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->iterator);
          this->__isset.iterator = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->primary.read(iprot);
          this->__isset.primary = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t IteratorPrimaryReturn::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("IteratorPrimaryReturn");

  xfer += oprot->writeFieldBegin("iterator", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->iterator);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("primary", ::apache::thrift::protocol::T_STRUCT, 2);
  xfer += this->primary.write(oprot);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(IteratorPrimaryReturn &a, IteratorPrimaryReturn &b) {
  using ::std::swap;
  swap(a.iterator, b.iterator);
  swap(a.primary, b.primary);
  swap(a.__isset, b.__isset);
}

IteratorPrimaryReturn::IteratorPrimaryReturn(const IteratorPrimaryReturn& other12) {
  iterator = other12.iterator;
  primary = other12.primary;
  __isset = other12.__isset;
}
IteratorPrimaryReturn& IteratorPrimaryReturn::operator=(const IteratorPrimaryReturn& other13) {
  iterator = other13.iterator;
  primary = other13.primary;
  __isset = other13.__isset;
  return *this;
}
void IteratorPrimaryReturn::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "IteratorPrimaryReturn(";
  out << "iterator=" << to_string(iterator);
  out << ", " << "primary=" << to_string(primary);
  out << ")";
}


FindPrimaryReturn::~FindPrimaryReturn() noexcept {
}


void FindPrimaryReturn::__set_iterator(const int32_t val) {
  this->iterator = val;
}

void FindPrimaryReturn::__set_secondary(const std::string& val) {
  this->secondary = val;
}
std::ostream& operator<<(std::ostream& out, const FindPrimaryReturn& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t FindPrimaryReturn::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->iterator);
          this->__isset.iterator = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->secondary);
          this->__isset.secondary = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t FindPrimaryReturn::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("FindPrimaryReturn");

  xfer += oprot->writeFieldBegin("iterator", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->iterator);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("secondary", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeBinary(this->secondary);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(FindPrimaryReturn &a, FindPrimaryReturn &b) {
  using ::std::swap;
  swap(a.iterator, b.iterator);
  swap(a.secondary, b.secondary);
  swap(a.__isset, b.__isset);
}

FindPrimaryReturn::FindPrimaryReturn(const FindPrimaryReturn& other14) {
  iterator = other14.iterator;
  secondary = other14.secondary;
  __isset = other14.__isset;
}
FindPrimaryReturn& FindPrimaryReturn::operator=(const FindPrimaryReturn& other15) {
  iterator = other15.iterator;
  secondary = other15.secondary;
  __isset = other15.__isset;
  return *this;
}
void FindPrimaryReturn::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "FindPrimaryReturn(";
  out << "iterator=" << to_string(iterator);
  out << ", " << "secondary=" << to_string(secondary);
  out << ")";
}


FindSecondaryReturn::~FindSecondaryReturn() noexcept {
}


void FindSecondaryReturn::__set_iterator(const int32_t val) {
  this->iterator = val;
}

void FindSecondaryReturn::__set_primary(const Uint64& val) {
  this->primary = val;
}
std::ostream& operator<<(std::ostream& out, const FindSecondaryReturn& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t FindSecondaryReturn::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->iterator);
          this->__isset.iterator = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->primary.read(iprot);
          this->__isset.primary = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t FindSecondaryReturn::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("FindSecondaryReturn");

  xfer += oprot->writeFieldBegin("iterator", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->iterator);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("primary", ::apache::thrift::protocol::T_STRUCT, 2);
  xfer += this->primary.write(oprot);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(FindSecondaryReturn &a, FindSecondaryReturn &b) {
  using ::std::swap;
  swap(a.iterator, b.iterator);
  swap(a.primary, b.primary);
  swap(a.__isset, b.__isset);
}

FindSecondaryReturn::FindSecondaryReturn(const FindSecondaryReturn& other16) {
  iterator = other16.iterator;
  primary = other16.primary;
  __isset = other16.__isset;
}
FindSecondaryReturn& FindSecondaryReturn::operator=(const FindSecondaryReturn& other17) {
  iterator = other17.iterator;
  primary = other17.primary;
  __isset = other17.__isset;
  return *this;
}
void FindSecondaryReturn::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "FindSecondaryReturn(";
  out << "iterator=" << to_string(iterator);
  out << ", " << "primary=" << to_string(primary);
  out << ")";
}


LowerBoundUpperBoundReturn::~LowerBoundUpperBoundReturn() noexcept {
}


void LowerBoundUpperBoundReturn::__set_iterator(const int32_t val) {
  this->iterator = val;
}

void LowerBoundUpperBoundReturn::__set_secondary(const std::string& val) {
  this->secondary = val;
}

void LowerBoundUpperBoundReturn::__set_primary(const Uint64& val) {
  this->primary = val;
}
std::ostream& operator<<(std::ostream& out, const LowerBoundUpperBoundReturn& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t LowerBoundUpperBoundReturn::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->iterator);
          this->__isset.iterator = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->secondary);
          this->__isset.secondary = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->primary.read(iprot);
          this->__isset.primary = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t LowerBoundUpperBoundReturn::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("LowerBoundUpperBoundReturn");

  xfer += oprot->writeFieldBegin("iterator", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->iterator);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("secondary", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeBinary(this->secondary);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("primary", ::apache::thrift::protocol::T_STRUCT, 3);
  xfer += this->primary.write(oprot);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(LowerBoundUpperBoundReturn &a, LowerBoundUpperBoundReturn &b) {
  using ::std::swap;
  swap(a.iterator, b.iterator);
  swap(a.secondary, b.secondary);
  swap(a.primary, b.primary);
  swap(a.__isset, b.__isset);
}

LowerBoundUpperBoundReturn::LowerBoundUpperBoundReturn(const LowerBoundUpperBoundReturn& other18) {
  iterator = other18.iterator;
  secondary = other18.secondary;
  primary = other18.primary;
  __isset = other18.__isset;
}
LowerBoundUpperBoundReturn& LowerBoundUpperBoundReturn::operator=(const LowerBoundUpperBoundReturn& other19) {
  iterator = other19.iterator;
  secondary = other19.secondary;
  primary = other19.primary;
  __isset = other19.__isset;
  return *this;
}
void LowerBoundUpperBoundReturn::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "LowerBoundUpperBoundReturn(";
  out << "iterator=" << to_string(iterator);
  out << ", " << "secondary=" << to_string(secondary);
  out << ", " << "primary=" << to_string(primary);
  out << ")";
}


GetResourceLimitsReturn::~GetResourceLimitsReturn() noexcept {
}


void GetResourceLimitsReturn::__set_ram_bytes(const int64_t val) {
  this->ram_bytes = val;
}

void GetResourceLimitsReturn::__set_net_weight(const int64_t val) {
  this->net_weight = val;
}

void GetResourceLimitsReturn::__set_cpu_weight(const int64_t val) {
  this->cpu_weight = val;
}
std::ostream& operator<<(std::ostream& out, const GetResourceLimitsReturn& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t GetResourceLimitsReturn::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->ram_bytes);
          this->__isset.ram_bytes = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->net_weight);
          this->__isset.net_weight = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->cpu_weight);
          this->__isset.cpu_weight = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t GetResourceLimitsReturn::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("GetResourceLimitsReturn");

  xfer += oprot->writeFieldBegin("ram_bytes", ::apache::thrift::protocol::T_I64, 1);
  xfer += oprot->writeI64(this->ram_bytes);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("net_weight", ::apache::thrift::protocol::T_I64, 2);
  xfer += oprot->writeI64(this->net_weight);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("cpu_weight", ::apache::thrift::protocol::T_I64, 3);
  xfer += oprot->writeI64(this->cpu_weight);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(GetResourceLimitsReturn &a, GetResourceLimitsReturn &b) {
  using ::std::swap;
  swap(a.ram_bytes, b.ram_bytes);
  swap(a.net_weight, b.net_weight);
  swap(a.cpu_weight, b.cpu_weight);
  swap(a.__isset, b.__isset);
}

GetResourceLimitsReturn::GetResourceLimitsReturn(const GetResourceLimitsReturn& other20) noexcept {
  ram_bytes = other20.ram_bytes;
  net_weight = other20.net_weight;
  cpu_weight = other20.cpu_weight;
  __isset = other20.__isset;
}
GetResourceLimitsReturn& GetResourceLimitsReturn::operator=(const GetResourceLimitsReturn& other21) noexcept {
  ram_bytes = other21.ram_bytes;
  net_weight = other21.net_weight;
  cpu_weight = other21.cpu_weight;
  __isset = other21.__isset;
  return *this;
}
void GetResourceLimitsReturn::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "GetResourceLimitsReturn(";
  out << "ram_bytes=" << to_string(ram_bytes);
  out << ", " << "net_weight=" << to_string(net_weight);
  out << ", " << "cpu_weight=" << to_string(cpu_weight);
  out << ")";
}

} // namespace