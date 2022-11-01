![build](https://github.com/uuosio/cpp-chaintester/actions/workflows/pr-any.yml/badge.svg?event=push)
[![codecov](https://codecov.io/gh/uuosio/cpp-chaintester/branch/main/graph/badge.svg?token=B1WQZRLLUI)](https://codecov.io/gh/uuosio/cpp-chaintester)

C++ Smart Contracts Test Framework for EOS

# What is cpp-chaintester

1. It is a C++ smart contracts test framework for EOS.
2. It makes writing C++ Smart Contracts test code more convenient.
3. It supports source-level C++ Smart Contracts debugging.
4. It supports generating code coverage reports for C++ Smart Contracts.

## Installing `ipyeos`

`cpp-chaintester` depends on [ipyeos](https://github.com/uuosio/ipyeos) to run your test code.

Install it with the following command:

```bash
python3 -m pip install -U ipyeos
```

Then run the debugging server:

```bash
eos-debugger
```

Also, you can run eos-debugger in a docker container. Just follow the steps below.

```bash
docker pull ghcr.io/uuosio/ipyeos:latest
```

Run the debugging server:

```bash
docker run -it --rm -p 9090:9090 -p 9092:9092 -t ghcr.io/uuosio/ipyeos
```

## Debugging

In order to support debugging, your project needs to compile with `Debug` mode

```bash
mkdir build
cd build
cmake -DENABLE_COVERAGE=TRUE -DBUILD_TESTS=TRUE -DCMAKE_BUILD_TYPE=Debug -Dcdt_DIR=`cdt-get-dir` -GNinja ..
```

### A Simple Example

```C++
TEST_CASE( "test hello", "[hello]" ) {
    ChainTester tester(true);
    tester.deploy_contract("hello"_n, HELLO_WASM, HELLO_ABI);

    tester.push_action(
        "hello"_n,
        "hello"_n,
        "sum"_n,
        std::make_tuple(uint64_t(1), uint64_t(2))
    );
    tester.produce_block();
}
```

### Debugging Example

Enable debugging by setting a native apply function

```C++
TEST_CASE( "test hello", "[hello]" ) {
    ChainTester tester(true);
    tester.set_native_apply("hello"_n, hello_native_apply);
    tester.deploy_contract("hello"_n, HELLO_WASM, HELLO_ABI);

    tester.push_action(
        "hello"_n,
        "hello"_n,
        "sum"_n,
        std::make_tuple(uint64_t(1), uint64_t(2))
    );
    tester.produce_block();
}
```

### Debugging Example 2

Enable debugging by setting a shared native contract lib.

```C++
TEST_CASE( "test hello", "[hello]" ) {
    ChainTester tester(true);
    tester.enable_debugging(true);
    tester.set_native_contract("hello"_n, HELLO_NATIVE_LIB);
    tester.deploy_contract("hello"_n, HELLO_WASM, HELLO_ABI);

    tester.push_action(
        "hello"_n,
        "hello"_n,
        "sum"_n,
        std::make_tuple(uint64_t(1), uint64_t(2))
    );
    tester.produce_block();
}
```

## Generating Code Coverage Report

Add `-fprofile-arcs -ftest-coverage` options to native library like below to support generating  coverage report for your code.

```cmake
target_compile_options(hello_native PRIVATE 
    -fprofile-arcs -ftest-coverage
    ...
)

target_link_options(hello_native PRIVATE -fprofile-arcs -ftest-coverage)
```

## C++ Smart Contracts Test Example

[cpp-coverage-example](https://github.com/uuosio/cpp-coverage-example) shows how to integrating cpp-chaintester in your smart contract project for debugging and generating code coverage report.


## Common ChainTester methods

### push_action

push an action to the test chain

```C++
template<typename... Ts>
std::shared_ptr<JsonObject> push_action(const vector<permission_level>& permissions, const name account, const name action, Ts... arguments);

template<typename... Ts>
std::shared_ptr<JsonObject> push_action(const name signer, const name account, const name action, Ts... arguments);
```

### push_actions

push actions to test chain

```C++
std::shared_ptr<JsonObject> push_actions(const std::vector<action>& actions);
```

### deploy_contract

```C++
std::shared_ptr<JsonObject> deploy_contract(const name account, const string& wasmFile, const string& abiFile);
```

### import_key

import private key for signing transaction

```C++
bool import_key(const string& pub_key, const string& priv_key);
```

### create_account

create an account

```C++
std::shared_ptr<JsonObject> create_account(const name creator, const name account, const string& owner_key, const string& active_key, int64_t ram_bytes=10*1024*1024, int64_t stake_net=100000, int64_t stake_cpu=1000000);
```

### produce_block

produce one block

```C++
void produce_block(int64_t next_block_delay_seconds = 0);
```

### produce_blocks

produce n block

```C++
void produce_blocks(int n);
```

### get_info

Get test chain information

```C++
    std::shared_ptr<JsonObject> get_info();
```

return value looks like below:

```json
{
      "server_version": "00000000",
      "chain_id": "fafc23d24da8824276b6949e065db4597f2b80cbd460ae2348db5faf7f5b9958",
      "head_block_num": 6,
      "last_irreversible_block_num": 5,
      "last_irreversible_block_id": "000000055b8a9d5b3a1ea3c729feb40796b7d7c61a8dc917a7aaaa1410d3bb79",
      "head_block_id": "00000006304b291f27b99ecf4b5cfcb910ad4b3fdb1cf890711a0b93d8f4d52a",
      "head_block_time": "2018-06-01T12:00:02.500",
      "head_block_producer": "eosio",
      "virtual_block_cpu_limit": 451802,
      "virtual_block_net_limit": 1053831,
      "block_cpu_limit": 449900,
      "block_net_limit": 1048576,
      "server_version_string": "Unknown",
      "fork_db_head_block_num": 6,
      "fork_db_head_block_id": "00000006304b291f27b99ecf4b5cfcb910ad4b3fdb1cf890711a0b93d8f4d52a",
      "server_full_version_string": "Unknown",
      "total_cpu_weight": 0,
      "total_net_weight": 0,
      "earliest_available_block_num": 1,
      "last_irreversible_block_time": "2018-06-01T12:00:02.000"
  }
```

### create_key

return a crypto key pair

```C++
std::shared_ptr<JsonObject> create_key(const char* key_type="K1");
```

return value like below:

```json
{
    "public": "EOS5EJKkpgHacHmnzqXj48AaZRL6zYTpKAPFreerTRhin3QtnByvt",
    "private": "..."
}
```

### get_account

get account information

```C++
std::shared_ptr<JsonObject> get_account(const name account);
```

return value like below:

```json
{
    "account_name": "hello",
    "head_block_num": 6,
    "head_block_time": "2018-06-01T12:00:02.500",
    "privileged": false,
    "last_code_update": "1970-01-01T00:00:00.000",
    "created": "2018-06-01T12:00:00.500",
    "core_liquid_balance": "5000000.0000 EOS",
    "ram_quota": -1,
    "net_weight": -1,
    "cpu_weight": -1,
    "net_limit": {
        "used": -1,
        "available": -1,
        "max": -1,
        "last_usage_update_time": "2018-06-01T12:00:00.500",
        "current_used": -1
    },
    "cpu_limit": {
        "used": -1,
        "available": -1,
        "max": -1,
        "last_usage_update_time": "2018-06-01T12:00:00.500",
        "current_used": -1
    },
    "ram_usage": 2724,
    "permissions": [
        {
            "perm_name": "active",
            "parent": "owner",
            "required_auth": {
                "threshold": 1,
                "keys": [
                    {
                        "key":
"EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV",
                        "weight": 1
                    }
                ],
                "accounts": [],
                "waits": []
            },
            "linked_actions": []
        },
        {
            "perm_name": "owner",
            "parent": "",
            "required_auth": {
                "threshold": 1,
                "keys": [
                    {
                        "key":
"EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV",
                        "weight": 1
                    }
                ],
                "accounts": [],
                "waits": []
            },
            "linked_actions": []
        }
    ],
    "total_resources": null,
    "self_delegated_bandwidth": null,
    "refund_request": null,
    "voter_info": null,
    "rex_info": null,
    "eosio_any_linked_actions": []
}
```

### get_table_rows

```C++
std::shared_ptr<JsonObject> get_table_rows(bool json,
                                const name code, const name scope, const name table,
                                const name lower_bound, const name upper_bound,
                                int64_t limit,
                                const string& key_type = "",
                                const string& index_position = "",
                                bool reverse = false,
                                bool show_payer = true);
```

### get_balance

get token balance of an account

```C++
int64_t get_balance(const name account, const name token_account="eosio.token"_n, const string& symbol="EOS");
```

## JsonObject methods

### get_string

return string value in a json object

```C++
template<typename... Ts>
string get_string(Ts... args)
```

Example:

```C++
std::shared_ptr<JsonObject> ret = this->get_table_rows(false, token_account, account, "accounts", symbol, "", 1);
if (!ret->has_value("rows", 0, "data")) {
    return;
}
string s = ret->get_string("rows", 0, "data");
```


### to_string

get json string

```C++
const string& to_string() const
```

### to_pretty_string

get pretty formatted json string

```C++
string to_pretty_string() const
```

## ActionSender

Example:

```C++
    ChainTester tester(true);
    tester.set_native_apply("hello"_n, hello_native_apply);
    tester.deploy_contract("hello"_n, HELLO_WASM, HELLO_ABI);
    
    ActionSender sender = tester.new_action_sender();
    sender.add_action(
        "hello"_n,
        "hello"_n,
        "sum"_n,
        std::make_tuple(uint64_t(1), uint64_t(2))
    );
    sender.send();
    tester.produce_block();
```

### add_action

add an action to the ActionSender

```C++
template<typename... Ts>
ActionSender& add_action(const name signer, name account, name action, Ts... args);

template<typename... Ts>
ActionSender& add_action(const vector<permission_level>& permissions, name account, name action, Ts... args);
```

### send

call `ChainTester.push_actions` to send the action(s)

```C++
    std::shared_ptr<JsonObject> send()
```
