#include "chaintester.h"

#include "intrinsics.h"
#include <string.h>


Uint64 to_raw_uint64(uint64_t value) {
    Uint64 _value;
    _value.rawValue = string((char *)&value, 8);
    return _value;
}

uint64_t from_raw_uint64(Uint64 value) {
    uint64_t _value;
    memcpy(&_value, value.rawValue.c_str(), 8);
    return _value;
}

std::shared_ptr<chaintester::ApplyClient> GetApplyClient();

uint32_t get_active_producers( capi_name* producers, uint32_t datalen ) {
    string ret;
    GetApplyClient()->get_active_producers(ret);
    if (datalen == 0) {
        return ret.size();
    }
    size_t copy_size = std::min(ret.size(), size_t(datalen));
    memcpy(producers, ret.c_str(), copy_size);
    return copy_size;
}

//db.h
// int32_t db_store_i64(uint64_t scope, capi_name table, capi_name payer, uint64_t id,  const void* data, uint32_t len);
// void db_update_i64(int32_t iterator, capi_name payer, const void* data, uint32_t len);
// void db_remove_i64(int32_t iterator);
// int32_t db_get_i64(int32_t iterator, const void* data, uint32_t len);
// int32_t db_next_i64(int32_t iterator, uint64_t* primary);
// int32_t db_previous_i64(int32_t iterator, uint64_t* primary);
// int32_t db_find_i64(capi_name code, uint64_t scope, capi_name table, uint64_t id);
// int32_t db_lowerbound_i64(capi_name code, uint64_t scope, capi_name table, uint64_t id);
// int32_t db_upperbound_i64(capi_name code, uint64_t scope, capi_name table, uint64_t id);
// int32_t db_end_i64(capi_name code, uint64_t scope, capi_name table);
// int32_t db_idx64_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const uint64_t* secondary);
// void db_idx64_update(int32_t iterator, capi_name payer, const uint64_t* secondary);
// void db_idx64_remove(int32_t iterator);
// int32_t db_idx64_next(int32_t iterator, uint64_t* primary);
// int32_t db_idx64_previous(int32_t iterator, uint64_t* primary);
// int32_t db_idx64_find_primary(capi_name code, uint64_t scope, capi_name table, uint64_t* secondary, uint64_t primary);
// int32_t db_idx64_find_secondary(capi_name code, uint64_t scope, capi_name table, const uint64_t* secondary, uint64_t* primary);
// int32_t db_idx64_lowerbound(capi_name code, uint64_t scope, capi_name table, uint64_t* secondary, uint64_t* primary);
// int32_t db_idx64_upperbound(capi_name code, uint64_t scope, capi_name table, uint64_t* secondary, uint64_t* primary);
// int32_t db_idx64_end(capi_name code, uint64_t scope, capi_name table);
// int32_t db_idx128_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const uint128_t* secondary);
// void db_idx128_update(int32_t iterator, capi_name payer, const uint128_t* secondary);
// void db_idx128_remove(int32_t iterator);
// int32_t db_idx128_next(int32_t iterator, uint64_t* primary);
// int32_t db_idx128_previous(int32_t iterator, uint64_t* primary);
// int32_t db_idx128_find_primary(capi_name code, uint64_t scope, capi_name table, uint128_t* secondary, uint64_t primary);
// int32_t db_idx128_find_secondary(capi_name code, uint64_t scope, capi_name table, const uint128_t* secondary, uint64_t* primary);
// int32_t db_idx128_lowerbound(capi_name code, uint64_t scope, capi_name table, uint128_t* secondary, uint64_t* primary);
// int32_t db_idx128_upperbound(capi_name code, uint64_t scope, capi_name table, uint128_t* secondary, uint64_t* primary);
// int32_t db_idx128_end(capi_name code, uint64_t scope, capi_name table);
// int32_t db_idx256_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const uint128_t* data, uint32_t data_len );
// void db_idx256_update(int32_t iterator, capi_name payer, const uint128_t* data, uint32_t data_len);
// void db_idx256_remove(int32_t iterator);
// int32_t db_idx256_next(int32_t iterator, uint64_t* primary);
// int32_t db_idx256_previous(int32_t iterator, uint64_t* primary);
// int32_t db_idx256_find_primary(capi_name code, uint64_t scope, capi_name table, uint128_t* data, uint32_t data_len, uint64_t primary);
// int32_t db_idx256_find_secondary(capi_name code, uint64_t scope, capi_name table, const uint128_t* data, uint32_t data_len, uint64_t* primary);
// int32_t db_idx256_lowerbound(capi_name code, uint64_t scope, capi_name table, uint128_t* data, uint32_t data_len, uint64_t* primary);
// int32_t db_idx256_upperbound(capi_name code, uint64_t scope, capi_name table, uint128_t* data, uint32_t data_len, uint64_t* primary);
// int32_t db_idx256_end(capi_name code, uint64_t scope, capi_name table);
// int32_t db_idx_double_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const double* secondary);
// void db_idx_double_update(int32_t iterator, capi_name payer, const double* secondary);
// void db_idx_double_remove(int32_t iterator);
// int32_t db_idx_double_next(int32_t iterator, uint64_t* primary);
// int32_t db_idx_double_previous(int32_t iterator, uint64_t* primary);
// int32_t db_idx_double_find_primary(capi_name code, uint64_t scope, capi_name table, double* secondary, uint64_t primary);
// int32_t db_idx_double_find_secondary(capi_name code, uint64_t scope, capi_name table, const double* secondary, uint64_t* primary);
// int32_t db_idx_double_lowerbound(capi_name code, uint64_t scope, capi_name table, double* secondary, uint64_t* primary);
// int32_t db_idx_double_upperbound(capi_name code, uint64_t scope, capi_name table, double* secondary, uint64_t* primary);
// int32_t db_idx_double_end(capi_name code, uint64_t scope, capi_name table);
// int32_t db_idx_long_double_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const long double* secondary);
// void db_idx_long_double_update(int32_t iterator, capi_name payer, const long double* secondary);
// void db_idx_long_double_remove(int32_t iterator);
// int32_t db_idx_long_double_next(int32_t iterator, uint64_t* primary);
// int32_t db_idx_long_double_previous(int32_t iterator, uint64_t* primary);
// int32_t db_idx_long_double_find_primary(capi_name code, uint64_t scope, capi_name table, long double* secondary, uint64_t primary);
// int32_t db_idx_long_double_find_secondary(capi_name code, uint64_t scope, capi_name table, const long double* secondary, uint64_t* primary);
// int32_t db_idx_long_double_lowerbound(capi_name code, uint64_t scope, capi_name table, long double* secondary, uint64_t* primary);
// int32_t db_idx_long_double_upperbound(capi_name code, uint64_t scope, capi_name table, long double* secondary, uint64_t* primary);
// int32_t db_idx_long_double_end(capi_name code, uint64_t scope, capi_name table);

int32_t check_transaction_authorization( const char* trx_data,     uint32_t trx_size,
                                 const char* pubkeys_data, uint32_t pubkeys_size,
                                 const char* perms_data,   uint32_t perms_size) {
    string _trx_data = string(trx_data, trx_size);
    string _pubkeys_data = string(pubkeys_data, pubkeys_size);
    string _perms_data = string(_perms_data, perms_size);
    return GetApplyClient()->check_transaction_authorization(_trx_data, _pubkeys_data, _perms_data);
}

int32_t check_permission_authorization( capi_name account,
                                capi_name permission,
                                const char* pubkeys_data, uint32_t pubkeys_size,
                                const char* perms_data,   uint32_t perms_size,
                                uint64_t delay_us) {
    auto _account = to_raw_uint64(account);
    auto _permission = to_raw_uint64(permission);
    auto _pubkeys_data = string(pubkeys_data, pubkeys_size);
    auto _perms_data = string(perms_data, perms_size);
    auto _delay_us =to_raw_uint64(delay_us);
    return GetApplyClient()->check_permission_authorization(_account, _permission, _pubkeys_data, _perms_data, _delay_us);
}

int64_t get_permission_last_used( capi_name account, capi_name permission ) {
    return GetApplyClient()->get_permission_last_used(to_raw_uint64(account), to_raw_uint64(permission));
}

int64_t get_account_creation_time( capi_name account ) {
    return GetApplyClient()->get_account_creation_time(to_raw_uint64(account));
}

void assert_sha256( const char* data, uint32_t length, const capi_checksum256* hash ) {
    GetApplyClient()->assert_sha256(string(data, length), string((char*)hash, 32));
}

void assert_sha1( const char* data, uint32_t length, const capi_checksum160* hash ) {
    GetApplyClient()->assert_sha1(string(data, length), string((char*)hash, 20));
}

void assert_sha512( const char* data, uint32_t length, const capi_checksum512* hash ) {
    GetApplyClient()->assert_sha512(string(data, length), string((char*)hash, 64));
}

void assert_ripemd160( const char* data, uint32_t length, const capi_checksum160* hash ) {
    GetApplyClient()->assert_ripemd160(string(data, length), string((char*)hash, 20));
}

void sha256( const char* data, uint32_t length, capi_checksum256* hash ) {
    string ret;
    GetApplyClient()->sha256(ret, string(data, length));
    memcpy(hash, ret.c_str(), 32);
}

void sha1( const char* data, uint32_t length, capi_checksum160* hash ) {
    string ret;
    GetApplyClient()->sha1(ret, string(data, length));
    memcpy(hash, ret.c_str(), 20);
}

void sha512( const char* data, uint32_t length, capi_checksum512* hash ) {
    string ret;
    GetApplyClient()->sha512(ret, string(data, length));
    memcpy(hash, ret.c_str(), 64);
}

void ripemd160( const char* data, uint32_t length, capi_checksum160* hash ) {
    string ret;
    GetApplyClient()->ripemd160(ret, string(data, length));
    memcpy(hash, ret.c_str(), 20);
}

int recover_key( const capi_checksum256* digest, const char* sig, size_t siglen, char* pub, size_t publen ) {
    string ret;
    GetApplyClient()->recover_key(ret, string((char*)digest, 32), string(sig, siglen));
    if (publen == 0) {
        return ret.size();
    }
    size_t copy_size = std::min(ret.size(), publen);
    memcpy(pub, ret.c_str(), copy_size);
    return copy_size;
}

void assert_recover_key( const capi_checksum256* digest, const char* sig, size_t siglen, const char* pub, size_t publen ) {
    GetApplyClient()->assert_recover_key(string((char*)digest, 32), string(sig, siglen), string(pub, publen));
}

uint32_t read_action_data( void* msg, uint32_t len ) {
    string ret;
    GetApplyClient()->read_action_data(ret);
    if (len == 0) {
        return ret.size();
    }
    size_t size = ret.size();
    if (size > len) {
        size = len;
    }
    memcpy(msg, ret.c_str(), size);
    return size;
}

uint32_t action_data_size() {
    return GetApplyClient()->action_data_size();
}

void require_recipient( capi_name name ) {
    GetApplyClient()->require_recipient(to_raw_uint64(name));
}

void require_auth( capi_name name ) {
    GetApplyClient()->require_auth(to_raw_uint64(name));
}

bool has_auth( capi_name name ) {
    return GetApplyClient()->has_auth(to_raw_uint64(name));
}

void require_auth2( capi_name name, capi_name permission ) {
    GetApplyClient()->require_auth2(to_raw_uint64(name), to_raw_uint64(permission));
}

bool is_account( capi_name name ) {
    return GetApplyClient()->is_account(to_raw_uint64(name));
}

void send_inline(char *serialized_action, size_t size) {
    GetApplyClient()->send_inline(string(serialized_action, size));
}

void send_context_free_inline(char *serialized_action, size_t size) {
    GetApplyClient()->send_context_free_inline(string(serialized_action, size));
}

uint64_t  publication_time() {
    Uint64 ret;
    GetApplyClient()->publication_time(ret);
    return  from_raw_uint64(ret);
}

capi_name current_receiver() {
    Uint64 ret;
    GetApplyClient()->current_receiver(ret);
    return from_raw_uint64(ret);
}

void prints( const char* cstr ) {
    GetApplyClient()->prints(string(cstr, strlen(cstr)));
}

void prints_l( const char* cstr, uint32_t len) {
    GetApplyClient()->prints(string(cstr, len));
}

void printi( int64_t value ) {
    GetApplyClient()->printi(value);
}

void printui( uint64_t value ) {
    Uint64 _value;
    _value.rawValue = string((char *)&value, 8);
    GetApplyClient()->printui(_value);
}

void printi128( const int128_t* value ) {
    string _value((char *)value, 16);
    GetApplyClient()->printi128(_value);
}

void printui128( const uint128_t* value ) {
    string _value((char *)value, 16);
    GetApplyClient()->printui128(_value);
}

void printsf(float value) {
    string _value((char *)&value, 4);
    GetApplyClient()->printsf(_value);
}

void printdf(double value) {
    string _value((char *)&value, 8);
    GetApplyClient()->printdf(_value);
}

void printqf(const long double* value) {
    string _value((char *)&value, 8);
    GetApplyClient()->printqf(_value);
}

void printn( uint64_t name ) {
    Uint64 _name;
    _name.rawValue = string((char *)&name, 8);
    GetApplyClient()->printn(_name);
}

void printhex( const void* data, uint32_t datalen ) {
    GetApplyClient()->printhex(string((char *)data, datalen));
}

void  eosio_assert( uint32_t test, const char* msg ) {
    GetApplyClient()->eosio_assert(test?1:0, string(msg));
}

void  eosio_assert_message( uint32_t test, const char* msg, uint32_t msg_len ) {
    GetApplyClient()->eosio_assert_message(test?1:0, string(msg, msg_len));
}

void  eosio_assert_code( uint32_t test, uint64_t code ) {
    GetApplyClient()->eosio_assert_code(test?1:0, to_raw_uint64(code));
}

uint64_t  current_time() {
    Uint64 value;
    GetApplyClient()->current_time(value);
    return from_raw_uint64(value);
}

bool is_feature_activated( const capi_checksum256* feature_digest ) {
    return GetApplyClient()->is_feature_activated(string((char *)feature_digest, 32));
}

capi_name get_sender() {
    Uint64 value;
    GetApplyClient()->get_sender(value);
    return from_raw_uint64(value);
}

void get_resource_limits( capi_name account, int64_t* ram_bytes, int64_t* net_weight, int64_t* cpu_weight ) {
    GetResourceLimitsReturn ret;
    Uint64 _account = to_raw_uint64(account);
    GetApplyClient()->get_resource_limits(ret, _account);
    *ram_bytes = ret.ram_bytes;
    *net_weight = ret.net_weight;
    *cpu_weight = ret.cpu_weight;
}

void set_resource_limits( capi_name account, int64_t ram_bytes, int64_t net_weight, int64_t cpu_weight ) {
    GetApplyClient()->set_resource_limits(to_raw_uint64(account), ram_bytes, net_weight, cpu_weight);
}

int64_t set_proposed_producers( char *producer_data, uint32_t producer_data_size ) {
    return GetApplyClient()->set_proposed_producers(string(producer_data, producer_data_size));
}

int64_t set_proposed_producers_ex( uint64_t producer_data_format, char *producer_data, uint32_t producer_data_size ) {
    return GetApplyClient()->set_proposed_producers_ex(to_raw_uint64(producer_data_format), string(producer_data, producer_data_size));
}

bool is_privileged( capi_name account ) {
    return GetApplyClient()->is_privileged(to_raw_uint64(account));
}

void set_privileged( capi_name account, bool is_priv ) {
    GetApplyClient()->set_privileged(to_raw_uint64(account), is_priv);
}

void set_blockchain_parameters_packed( char* data, uint32_t datalen ) {
    GetApplyClient()->set_blockchain_parameters_packed(string(data, datalen));
}

uint32_t get_blockchain_parameters_packed( char* data, uint32_t datalen ) {
    string ret;
    if (data == nullptr | datalen == 0) {
        return ret.size();
    }
    GetApplyClient()->get_blockchain_parameters_packed(ret);
    if (ret.size() <= datalen) {
        memcpy(data, ret.c_str(), ret.size());
        return ret.size();
    }
    return 0;
}

void preactivate_feature( const capi_checksum256* feature_digest ) {
    GetApplyClient()->preactivate_feature(string((char *)feature_digest, 32));
}

void send_deferred(const uint128_t& sender_id, capi_name payer, const char *serialized_transaction, size_t size, uint32_t replace_existing) {
    GetApplyClient()->send_deferred(string((char *)&sender_id, 16), to_raw_uint64(payer), string(serialized_transaction, size), replace_existing);
}

int cancel_deferred(const uint128_t& sender_id) {
    return GetApplyClient()->cancel_deferred(string((char*)&sender_id, 16));
}

size_t read_transaction(char *buffer, size_t size) {
    string ret;
    GetApplyClient()->read_transaction(ret);
    if (size == 0) {
        return ret.size();
    }
    size_t copy_size = std::min(ret.size(), size);
    memcpy(buffer, ret.c_str(), ret.size());
    return copy_size;
}

size_t transaction_size() {
    return GetApplyClient()->transaction_size();
}

int tapos_block_num() {
    return GetApplyClient()->tapos_block_num();
}

int tapos_block_prefix() {
    return GetApplyClient()->tapos_block_prefix();
}

uint32_t expiration() {
    return GetApplyClient()->expiration();
}

int get_action( uint32_t type, uint32_t index, char* buff, size_t size ) {
    string ret;
    GetApplyClient()->get_action(ret, type, index);
    if (size == 0) {
        return ret.size();
    }
    size_t copy_size = std::min(ret.size(), size);
    memcpy(buff, ret.c_str(), ret.size());
    return copy_size;
}

int get_context_free_data( uint32_t index, char* buff, size_t size ) {
    string ret;
    GetApplyClient()->get_context_free_data(ret, index);
    if (size == 0) {
        return ret.size();
    }
    size_t copy_size = std::min(ret.size(), size);
    memcpy(buff, ret.c_str(), ret.size());
    return copy_size;
}
