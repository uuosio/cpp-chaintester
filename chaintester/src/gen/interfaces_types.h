/**
 * Autogenerated by Thrift Compiler (0.15.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef interfaces_TYPES_H
#define interfaces_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <functional>
#include <memory>


namespace chaintester {

class TransactionException;

class AssertException;

class ActionArguments;

class Action;

class Uint64;

class DataBuffer;

class NextPreviousReturn;

class IteratorPrimaryReturn;

class FindPrimaryReturn;

class FindSecondaryReturn;

class LowerBoundUpperBoundReturn;

class GetResourceLimitsReturn;

typedef struct _TransactionException__isset {
  _TransactionException__isset() : exc(false) {}
  bool exc :1;
} _TransactionException__isset;

class TransactionException : public ::apache::thrift::TException {
 public:

  TransactionException(const TransactionException&);
  TransactionException& operator=(const TransactionException&);
  TransactionException() noexcept
                       : exc() {
  }

  virtual ~TransactionException() noexcept;
  std::string exc;

  _TransactionException__isset __isset;

  void __set_exc(const std::string& val);

  bool operator == (const TransactionException & rhs) const
  {
    if (!(exc == rhs.exc))
      return false;
    return true;
  }
  bool operator != (const TransactionException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TransactionException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept override;
};

void swap(TransactionException &a, TransactionException &b);

std::ostream& operator<<(std::ostream& out, const TransactionException& obj);

typedef struct _AssertException__isset {
  _AssertException__isset() : error_message(false) {}
  bool error_message :1;
} _AssertException__isset;

class AssertException : public ::apache::thrift::TException {
 public:

  AssertException(const AssertException&);
  AssertException& operator=(const AssertException&);
  AssertException() noexcept
                  : error_message() {
  }

  virtual ~AssertException() noexcept;
  std::string error_message;

  _AssertException__isset __isset;

  void __set_error_message(const std::string& val);

  bool operator == (const AssertException & rhs) const
  {
    if (!(error_message == rhs.error_message))
      return false;
    return true;
  }
  bool operator != (const AssertException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const AssertException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept override;
};

void swap(AssertException &a, AssertException &b);

std::ostream& operator<<(std::ostream& out, const AssertException& obj);

typedef struct _ActionArguments__isset {
  _ActionArguments__isset() : raw_args(false), json_args(false) {}
  bool raw_args :1;
  bool json_args :1;
} _ActionArguments__isset;

class ActionArguments : public virtual ::apache::thrift::TBase {
 public:

  ActionArguments(const ActionArguments&);
  ActionArguments& operator=(const ActionArguments&);
  ActionArguments() noexcept
                  : raw_args(),
                    json_args() {
  }

  virtual ~ActionArguments() noexcept;
  std::string raw_args;
  std::string json_args;

  _ActionArguments__isset __isset;

  void __set_raw_args(const std::string& val);

  void __set_json_args(const std::string& val);

  bool operator == (const ActionArguments & rhs) const
  {
    if (__isset.raw_args != rhs.__isset.raw_args)
      return false;
    else if (__isset.raw_args && !(raw_args == rhs.raw_args))
      return false;
    if (__isset.json_args != rhs.__isset.json_args)
      return false;
    else if (__isset.json_args && !(json_args == rhs.json_args))
      return false;
    return true;
  }
  bool operator != (const ActionArguments &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ActionArguments & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot) override;
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const override;

  virtual void printTo(std::ostream& out) const;
};

void swap(ActionArguments &a, ActionArguments &b);

std::ostream& operator<<(std::ostream& out, const ActionArguments& obj);

typedef struct _Action__isset {
  _Action__isset() : account(false), action(false), permissions(false), arguments(false) {}
  bool account :1;
  bool action :1;
  bool permissions :1;
  bool arguments :1;
} _Action__isset;

class Action : public virtual ::apache::thrift::TBase {
 public:

  Action(const Action&);
  Action& operator=(const Action&);
  Action() noexcept
         : account(),
           action(),
           permissions() {
  }

  virtual ~Action() noexcept;
  std::string account;
  std::string action;
  std::string permissions;
  ActionArguments arguments;

  _Action__isset __isset;

  void __set_account(const std::string& val);

  void __set_action(const std::string& val);

  void __set_permissions(const std::string& val);

  void __set_arguments(const ActionArguments& val);

  bool operator == (const Action & rhs) const
  {
    if (!(account == rhs.account))
      return false;
    if (!(action == rhs.action))
      return false;
    if (!(permissions == rhs.permissions))
      return false;
    if (!(arguments == rhs.arguments))
      return false;
    return true;
  }
  bool operator != (const Action &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Action & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot) override;
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const override;

  virtual void printTo(std::ostream& out) const;
};

void swap(Action &a, Action &b);

std::ostream& operator<<(std::ostream& out, const Action& obj);

typedef struct _Uint64__isset {
  _Uint64__isset() : rawValue(false) {}
  bool rawValue :1;
} _Uint64__isset;

class Uint64 : public virtual ::apache::thrift::TBase {
 public:

  Uint64(const Uint64&);
  Uint64& operator=(const Uint64&);
  Uint64() noexcept
         : rawValue() {
  }

  virtual ~Uint64() noexcept;
  std::string rawValue;

  _Uint64__isset __isset;

  void __set_rawValue(const std::string& val);

  bool operator == (const Uint64 & rhs) const
  {
    if (!(rawValue == rhs.rawValue))
      return false;
    return true;
  }
  bool operator != (const Uint64 &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Uint64 & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot) override;
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const override;

  virtual void printTo(std::ostream& out) const;
};

void swap(Uint64 &a, Uint64 &b);

std::ostream& operator<<(std::ostream& out, const Uint64& obj);

typedef struct _DataBuffer__isset {
  _DataBuffer__isset() : size(false), buffer(false) {}
  bool size :1;
  bool buffer :1;
} _DataBuffer__isset;

class DataBuffer : public virtual ::apache::thrift::TBase {
 public:

  DataBuffer(const DataBuffer&);
  DataBuffer& operator=(const DataBuffer&);
  DataBuffer() noexcept
             : size(0),
               buffer() {
  }

  virtual ~DataBuffer() noexcept;
  int32_t size;
  std::string buffer;

  _DataBuffer__isset __isset;

  void __set_size(const int32_t val);

  void __set_buffer(const std::string& val);

  bool operator == (const DataBuffer & rhs) const
  {
    if (!(size == rhs.size))
      return false;
    if (!(buffer == rhs.buffer))
      return false;
    return true;
  }
  bool operator != (const DataBuffer &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DataBuffer & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot) override;
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const override;

  virtual void printTo(std::ostream& out) const;
};

void swap(DataBuffer &a, DataBuffer &b);

std::ostream& operator<<(std::ostream& out, const DataBuffer& obj);

typedef struct _NextPreviousReturn__isset {
  _NextPreviousReturn__isset() : iterator(false), primary(false) {}
  bool iterator :1;
  bool primary :1;
} _NextPreviousReturn__isset;

class NextPreviousReturn : public virtual ::apache::thrift::TBase {
 public:

  NextPreviousReturn(const NextPreviousReturn&);
  NextPreviousReturn& operator=(const NextPreviousReturn&);
  NextPreviousReturn() noexcept
                     : iterator(0) {
  }

  virtual ~NextPreviousReturn() noexcept;
  int32_t iterator;
  Uint64 primary;

  _NextPreviousReturn__isset __isset;

  void __set_iterator(const int32_t val);

  void __set_primary(const Uint64& val);

  bool operator == (const NextPreviousReturn & rhs) const
  {
    if (!(iterator == rhs.iterator))
      return false;
    if (!(primary == rhs.primary))
      return false;
    return true;
  }
  bool operator != (const NextPreviousReturn &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const NextPreviousReturn & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot) override;
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const override;

  virtual void printTo(std::ostream& out) const;
};

void swap(NextPreviousReturn &a, NextPreviousReturn &b);

std::ostream& operator<<(std::ostream& out, const NextPreviousReturn& obj);

typedef struct _IteratorPrimaryReturn__isset {
  _IteratorPrimaryReturn__isset() : iterator(false), primary(false) {}
  bool iterator :1;
  bool primary :1;
} _IteratorPrimaryReturn__isset;

class IteratorPrimaryReturn : public virtual ::apache::thrift::TBase {
 public:

  IteratorPrimaryReturn(const IteratorPrimaryReturn&);
  IteratorPrimaryReturn& operator=(const IteratorPrimaryReturn&);
  IteratorPrimaryReturn() noexcept
                        : iterator(0) {
  }

  virtual ~IteratorPrimaryReturn() noexcept;
  int32_t iterator;
  Uint64 primary;

  _IteratorPrimaryReturn__isset __isset;

  void __set_iterator(const int32_t val);

  void __set_primary(const Uint64& val);

  bool operator == (const IteratorPrimaryReturn & rhs) const
  {
    if (!(iterator == rhs.iterator))
      return false;
    if (!(primary == rhs.primary))
      return false;
    return true;
  }
  bool operator != (const IteratorPrimaryReturn &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const IteratorPrimaryReturn & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot) override;
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const override;

  virtual void printTo(std::ostream& out) const;
};

void swap(IteratorPrimaryReturn &a, IteratorPrimaryReturn &b);

std::ostream& operator<<(std::ostream& out, const IteratorPrimaryReturn& obj);

typedef struct _FindPrimaryReturn__isset {
  _FindPrimaryReturn__isset() : iterator(false), secondary(false) {}
  bool iterator :1;
  bool secondary :1;
} _FindPrimaryReturn__isset;

class FindPrimaryReturn : public virtual ::apache::thrift::TBase {
 public:

  FindPrimaryReturn(const FindPrimaryReturn&);
  FindPrimaryReturn& operator=(const FindPrimaryReturn&);
  FindPrimaryReturn() noexcept
                    : iterator(0),
                      secondary() {
  }

  virtual ~FindPrimaryReturn() noexcept;
  int32_t iterator;
  std::string secondary;

  _FindPrimaryReturn__isset __isset;

  void __set_iterator(const int32_t val);

  void __set_secondary(const std::string& val);

  bool operator == (const FindPrimaryReturn & rhs) const
  {
    if (!(iterator == rhs.iterator))
      return false;
    if (!(secondary == rhs.secondary))
      return false;
    return true;
  }
  bool operator != (const FindPrimaryReturn &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FindPrimaryReturn & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot) override;
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const override;

  virtual void printTo(std::ostream& out) const;
};

void swap(FindPrimaryReturn &a, FindPrimaryReturn &b);

std::ostream& operator<<(std::ostream& out, const FindPrimaryReturn& obj);

typedef struct _FindSecondaryReturn__isset {
  _FindSecondaryReturn__isset() : iterator(false), primary(false) {}
  bool iterator :1;
  bool primary :1;
} _FindSecondaryReturn__isset;

class FindSecondaryReturn : public virtual ::apache::thrift::TBase {
 public:

  FindSecondaryReturn(const FindSecondaryReturn&);
  FindSecondaryReturn& operator=(const FindSecondaryReturn&);
  FindSecondaryReturn() noexcept
                      : iterator(0) {
  }

  virtual ~FindSecondaryReturn() noexcept;
  int32_t iterator;
  Uint64 primary;

  _FindSecondaryReturn__isset __isset;

  void __set_iterator(const int32_t val);

  void __set_primary(const Uint64& val);

  bool operator == (const FindSecondaryReturn & rhs) const
  {
    if (!(iterator == rhs.iterator))
      return false;
    if (!(primary == rhs.primary))
      return false;
    return true;
  }
  bool operator != (const FindSecondaryReturn &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FindSecondaryReturn & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot) override;
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const override;

  virtual void printTo(std::ostream& out) const;
};

void swap(FindSecondaryReturn &a, FindSecondaryReturn &b);

std::ostream& operator<<(std::ostream& out, const FindSecondaryReturn& obj);

typedef struct _LowerBoundUpperBoundReturn__isset {
  _LowerBoundUpperBoundReturn__isset() : iterator(false), secondary(false), primary(false) {}
  bool iterator :1;
  bool secondary :1;
  bool primary :1;
} _LowerBoundUpperBoundReturn__isset;

class LowerBoundUpperBoundReturn : public virtual ::apache::thrift::TBase {
 public:

  LowerBoundUpperBoundReturn(const LowerBoundUpperBoundReturn&);
  LowerBoundUpperBoundReturn& operator=(const LowerBoundUpperBoundReturn&);
  LowerBoundUpperBoundReturn() noexcept
                             : iterator(0),
                               secondary() {
  }

  virtual ~LowerBoundUpperBoundReturn() noexcept;
  int32_t iterator;
  std::string secondary;
  Uint64 primary;

  _LowerBoundUpperBoundReturn__isset __isset;

  void __set_iterator(const int32_t val);

  void __set_secondary(const std::string& val);

  void __set_primary(const Uint64& val);

  bool operator == (const LowerBoundUpperBoundReturn & rhs) const
  {
    if (!(iterator == rhs.iterator))
      return false;
    if (!(secondary == rhs.secondary))
      return false;
    if (!(primary == rhs.primary))
      return false;
    return true;
  }
  bool operator != (const LowerBoundUpperBoundReturn &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LowerBoundUpperBoundReturn & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot) override;
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const override;

  virtual void printTo(std::ostream& out) const;
};

void swap(LowerBoundUpperBoundReturn &a, LowerBoundUpperBoundReturn &b);

std::ostream& operator<<(std::ostream& out, const LowerBoundUpperBoundReturn& obj);

typedef struct _GetResourceLimitsReturn__isset {
  _GetResourceLimitsReturn__isset() : ram_bytes(false), net_weight(false), cpu_weight(false) {}
  bool ram_bytes :1;
  bool net_weight :1;
  bool cpu_weight :1;
} _GetResourceLimitsReturn__isset;

class GetResourceLimitsReturn : public virtual ::apache::thrift::TBase {
 public:

  GetResourceLimitsReturn(const GetResourceLimitsReturn&) noexcept;
  GetResourceLimitsReturn& operator=(const GetResourceLimitsReturn&) noexcept;
  GetResourceLimitsReturn() noexcept
                          : ram_bytes(0),
                            net_weight(0),
                            cpu_weight(0) {
  }

  virtual ~GetResourceLimitsReturn() noexcept;
  int64_t ram_bytes;
  int64_t net_weight;
  int64_t cpu_weight;

  _GetResourceLimitsReturn__isset __isset;

  void __set_ram_bytes(const int64_t val);

  void __set_net_weight(const int64_t val);

  void __set_cpu_weight(const int64_t val);

  bool operator == (const GetResourceLimitsReturn & rhs) const
  {
    if (!(ram_bytes == rhs.ram_bytes))
      return false;
    if (!(net_weight == rhs.net_weight))
      return false;
    if (!(cpu_weight == rhs.cpu_weight))
      return false;
    return true;
  }
  bool operator != (const GetResourceLimitsReturn &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const GetResourceLimitsReturn & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot) override;
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const override;

  virtual void printTo(std::ostream& out) const;
};

void swap(GetResourceLimitsReturn &a, GetResourceLimitsReturn &b);

std::ostream& operator<<(std::ostream& out, const GetResourceLimitsReturn& obj);

} // namespace

#endif
