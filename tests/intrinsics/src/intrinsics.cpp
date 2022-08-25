#include "intrinsics.h"

uint32_t get_active_producers( capi_name* producers, uint32_t datalen ){
    return get_intrinsics()->get_active_producers(producers, datalen);
}

int32_t db_store_i64(uint64_t scope, capi_name table, capi_name payer, uint64_t id,  const void* data, uint32_t len){
    return get_intrinsics()->db_store_i64(scope, table, payer, id, data, len);
}

void db_update_i64(int32_t iterator, capi_name payer, const void* data, uint32_t len){
    get_intrinsics()->db_update_i64(iterator, payer, data, len);
}

void db_remove_i64(int32_t iterator){
    get_intrinsics()->db_remove_i64(iterator);
}

int32_t db_get_i64(int32_t iterator, const void* data, uint32_t len){
    return get_intrinsics()->db_get_i64(iterator, (void *)data, len);
}

int32_t db_next_i64(int32_t iterator, uint64_t* primary){
    return get_intrinsics()->db_next_i64(iterator, primary);
}

int32_t db_previous_i64(int32_t iterator, uint64_t* primary){
    return get_intrinsics()->db_previous_i64(iterator, primary);
}

int32_t db_find_i64(capi_name code, uint64_t scope, capi_name table, uint64_t id){
    return get_intrinsics()->db_find_i64(code, scope, table, id);
}

int32_t db_lowerbound_i64(capi_name code, uint64_t scope, capi_name table, uint64_t id){
    return get_intrinsics()->db_lowerbound_i64(code, scope, table, id);
}

int32_t db_upperbound_i64(capi_name code, uint64_t scope, capi_name table, uint64_t id){
    return get_intrinsics()->db_upperbound_i64(code, scope, table, id);
}

int32_t db_end_i64(capi_name code, uint64_t scope, capi_name table){
    return get_intrinsics()->db_end_i64(code, scope, table);
}

int32_t db_idx64_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const uint64_t* secondary){
    return get_intrinsics()->db_idx64_store(scope, table, payer, id, secondary);
}

void db_idx64_update(int32_t iterator, capi_name payer, const uint64_t* secondary){
    get_intrinsics()->db_idx64_update(iterator, payer, secondary);
}

void db_idx64_remove(int32_t iterator){
    get_intrinsics()->db_idx64_remove(iterator);
}

int32_t db_idx64_next(int32_t iterator, uint64_t* primary){
    return get_intrinsics()->db_idx64_next(iterator, primary);
}

int32_t db_idx64_previous(int32_t iterator, uint64_t* primary){
    return get_intrinsics()->db_idx64_previous(iterator, primary);
}

int32_t db_idx64_find_primary(capi_name code, uint64_t scope, capi_name table, uint64_t* secondary, uint64_t primary){
    return get_intrinsics()->db_idx64_find_primary(code, scope, table, secondary, primary);
}

int32_t db_idx64_find_secondary(capi_name code, uint64_t scope, capi_name table, const uint64_t* secondary, uint64_t* primary){
    return get_intrinsics()->db_idx64_find_secondary(code, scope, table, secondary, primary);
}

int32_t db_idx64_lowerbound(capi_name code, uint64_t scope, capi_name table, uint64_t* secondary, uint64_t* primary){
    return get_intrinsics()->db_idx64_lowerbound(code, scope, table, secondary, primary);
}

int32_t db_idx64_upperbound(capi_name code, uint64_t scope, capi_name table, uint64_t* secondary, uint64_t* primary){
    return get_intrinsics()->db_idx64_upperbound(code, scope, table, secondary, primary);
}

int32_t db_idx64_end(capi_name code, uint64_t scope, capi_name table){
    return get_intrinsics()->db_idx64_end(code, scope, table);
}

int32_t db_idx128_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const uint128_t* secondary){
    return get_intrinsics()->db_idx128_store(scope, table, payer, id, secondary);
}

void db_idx128_update(int32_t iterator, capi_name payer, const uint128_t* secondary){
    get_intrinsics()->db_idx128_update(iterator, payer, secondary);
}

void db_idx128_remove(int32_t iterator){
    get_intrinsics()->db_idx128_remove(iterator);
}

int32_t db_idx128_next(int32_t iterator, uint64_t* primary){
    return get_intrinsics()->db_idx128_next(iterator, primary);
}

int32_t db_idx128_previous(int32_t iterator, uint64_t* primary){
    return get_intrinsics()->db_idx128_previous(iterator, primary);
}

int32_t db_idx128_find_primary(capi_name code, uint64_t scope, capi_name table, uint128_t* secondary, uint64_t primary){
    return get_intrinsics()->db_idx128_find_primary(code, scope, table, secondary, primary);
}

int32_t db_idx128_find_secondary(capi_name code, uint64_t scope, capi_name table, const uint128_t* secondary, uint64_t* primary){
    return get_intrinsics()->db_idx128_find_secondary(code, scope, table, secondary, primary);
}

int32_t db_idx128_lowerbound(capi_name code, uint64_t scope, capi_name table, uint128_t* secondary, uint64_t* primary){
    return get_intrinsics()->db_idx128_lowerbound(code, scope, table, secondary, primary);
}

int32_t db_idx128_upperbound(capi_name code, uint64_t scope, capi_name table, uint128_t* secondary, uint64_t* primary){
    return get_intrinsics()->db_idx128_upperbound(code, scope, table, secondary, primary);
}

int32_t db_idx128_end(capi_name code, uint64_t scope, capi_name table){
    return get_intrinsics()->db_idx128_end(code, scope, table);
}

int32_t db_idx256_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const uint128_t* data, uint32_t data_len ){
    return get_intrinsics()->db_idx256_store(scope, table, payer, id, data, data_len);
}

void db_idx256_update(int32_t iterator, capi_name payer, const uint128_t* data, uint32_t data_len){
    get_intrinsics()->db_idx256_update(iterator, payer, data, data_len);
}

void db_idx256_remove(int32_t iterator){
    get_intrinsics()->db_idx256_remove(iterator);
}

int32_t db_idx256_next(int32_t iterator, uint64_t* primary){
    return get_intrinsics()->db_idx256_next(iterator, primary);
}

int32_t db_idx256_previous(int32_t iterator, uint64_t* primary){
    return get_intrinsics()->db_idx256_previous(iterator, primary);
}

int32_t db_idx256_find_primary(capi_name code, uint64_t scope, capi_name table, uint128_t* data, uint32_t data_len, uint64_t primary){
    return get_intrinsics()->db_idx256_find_primary(code, scope, table, data, data_len, primary);
}

int32_t db_idx256_find_secondary(capi_name code, uint64_t scope, capi_name table, const uint128_t* data, uint32_t data_len, uint64_t* primary){
    return get_intrinsics()->db_idx256_find_secondary(code, scope, table, data, data_len, primary);
}

int32_t db_idx256_lowerbound(capi_name code, uint64_t scope, capi_name table, uint128_t* data, uint32_t data_len, uint64_t* primary){
    return get_intrinsics()->db_idx256_lowerbound(code, scope, table, data, data_len, primary);
}

int32_t db_idx256_upperbound(capi_name code, uint64_t scope, capi_name table, uint128_t* data, uint32_t data_len, uint64_t* primary){
    return get_intrinsics()->db_idx256_upperbound(code, scope, table, data, data_len, primary);
}

int32_t db_idx256_end(capi_name code, uint64_t scope, capi_name table){
    return get_intrinsics()->db_idx256_end(code, scope, table);
}

int32_t db_idx_double_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const double* secondary){
    return get_intrinsics()->db_idx_double_store(scope, table, payer, id, secondary);
}

void db_idx_double_update(int32_t iterator, capi_name payer, const double* secondary){
    get_intrinsics()->db_idx_double_update(iterator, payer, secondary);
}

void db_idx_double_remove(int32_t iterator){
    get_intrinsics()->db_idx_double_remove(iterator);
}

int32_t db_idx_double_next(int32_t iterator, uint64_t* primary){
    return get_intrinsics()->db_idx_double_next(iterator, primary);
}

int32_t db_idx_double_previous(int32_t iterator, uint64_t* primary){
    return get_intrinsics()->db_idx_double_previous(iterator, primary);
}

int32_t db_idx_double_find_primary(capi_name code, uint64_t scope, capi_name table, double* secondary, uint64_t primary){
    return get_intrinsics()->db_idx_double_find_primary(code, scope, table, secondary, primary);
}

int32_t db_idx_double_find_secondary(capi_name code, uint64_t scope, capi_name table, const double* secondary, uint64_t* primary){
    return get_intrinsics()->db_idx_double_find_secondary(code, scope, table, secondary, primary);
}

int32_t db_idx_double_lowerbound(capi_name code, uint64_t scope, capi_name table, double* secondary, uint64_t* primary){
    return get_intrinsics()->db_idx_double_lowerbound(code, scope, table, secondary, primary);
}

int32_t db_idx_double_upperbound(capi_name code, uint64_t scope, capi_name table, double* secondary, uint64_t* primary){
    return get_intrinsics()->db_idx_double_upperbound(code, scope, table, secondary, primary);
}

int32_t db_idx_double_end(capi_name code, uint64_t scope, capi_name table){
    return get_intrinsics()->db_idx_double_end(code, scope, table);
}

int32_t db_idx_long_double_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const long double* secondary){
    return get_intrinsics()->db_idx_long_double_store(scope, table, payer, id, secondary);
}

void db_idx_long_double_update(int32_t iterator, capi_name payer, const long double* secondary){
    get_intrinsics()->db_idx_long_double_update(iterator, payer, secondary);
}

void db_idx_long_double_remove(int32_t iterator){
    get_intrinsics()->db_idx_long_double_remove(iterator);
}

int32_t db_idx_long_double_next(int32_t iterator, uint64_t* primary){
    return get_intrinsics()->db_idx_long_double_next(iterator, primary);
}

int32_t db_idx_long_double_previous(int32_t iterator, uint64_t* primary){
    return get_intrinsics()->db_idx_long_double_previous(iterator, primary);
}

int32_t db_idx_long_double_find_primary(capi_name code, uint64_t scope, capi_name table, long double* secondary, uint64_t primary){
    return get_intrinsics()->db_idx_long_double_find_primary(code, scope, table, secondary, primary);
}

int32_t db_idx_long_double_find_secondary(capi_name code, uint64_t scope, capi_name table, const long double* secondary, uint64_t* primary){
    return get_intrinsics()->db_idx_long_double_find_secondary(code, scope, table, secondary, primary);
}

int32_t db_idx_long_double_lowerbound(capi_name code, uint64_t scope, capi_name table, long double* secondary, uint64_t* primary){
    return get_intrinsics()->db_idx_long_double_lowerbound(code, scope, table, secondary, primary);
}

int32_t db_idx_long_double_upperbound(capi_name code, uint64_t scope, capi_name table, long double* secondary, uint64_t* primary){
    return get_intrinsics()->db_idx_long_double_upperbound(code, scope, table, secondary, primary);
}

int32_t db_idx_long_double_end(capi_name code, uint64_t scope, capi_name table){
    return get_intrinsics()->db_idx_long_double_end(code, scope, table);
}

int32_t check_transaction_authorization( const char* trx_data,     uint32_t trx_size, const char* pubkeys_data, uint32_t pubkeys_size,const char* perms_data,   uint32_t perms_size){
    return get_intrinsics()->check_transaction_authorization(trx_data, trx_size, pubkeys_data, pubkeys_size, perms_data, perms_size);
}

int32_t check_permission_authorization( capi_name account, capi_name permission, const char* pubkeys_data, uint32_t pubkeys_size, const char* perms_data,   uint32_t perms_size, uint64_t delay_us){
    return get_intrinsics()->check_permission_authorization(account, permission, pubkeys_data, pubkeys_size, perms_data, perms_size, delay_us);
}

int64_t get_permission_last_used( capi_name account, capi_name permission ){
    return get_intrinsics()->get_permission_last_used(account, permission);
}

int64_t get_account_creation_time( capi_name account ){
    return get_intrinsics()->get_account_creation_time(account);
}

void assert_sha256( const char* data, uint32_t length, const capi_checksum256* hash ){
    get_intrinsics()->assert_sha256(data, length, hash);
}

void assert_sha1( const char* data, uint32_t length, const capi_checksum160* hash ){
    get_intrinsics()->assert_sha1(data, length, hash);
}

void assert_sha512( const char* data, uint32_t length, const capi_checksum512* hash ){
    get_intrinsics()->assert_sha512(data, length, hash);
}

void assert_ripemd160( const char* data, uint32_t length, const capi_checksum160* hash ){
    get_intrinsics()->assert_ripemd160(data, length, hash);
}

void sha256( const char* data, uint32_t length, capi_checksum256* hash ){
    get_intrinsics()->sha256(data, length, hash);
}

void sha1( const char* data, uint32_t length, capi_checksum160* hash ){
    get_intrinsics()->sha1(data, length, hash);
}

void sha512( const char* data, uint32_t length, capi_checksum512* hash ){
    get_intrinsics()->sha512(data, length, hash);
}

void ripemd160( const char* data, uint32_t length, capi_checksum160* hash ){
    get_intrinsics()->ripemd160(data, length, hash);
}

int recover_key( const capi_checksum256* digest, const char* sig, size_t siglen, char* pub, size_t publen ){
    return get_intrinsics()->recover_key(digest, sig, siglen, pub, publen);
}

void assert_recover_key( const capi_checksum256* digest, const char* sig, size_t siglen, const char* pub, size_t publen ){
    get_intrinsics()->assert_recover_key(digest, sig, siglen, pub, publen);
}

uint32_t read_action_data( void* msg, uint32_t len ){
    return get_intrinsics()->read_action_data(msg, len);
}

uint32_t action_data_size(){
    return get_intrinsics()->action_data_size();
}

void require_recipient( capi_name name ){
    get_intrinsics()->require_recipient(name);
}

void require_auth( capi_name name ){
    get_intrinsics()->require_auth(name);
}

bool has_auth( capi_name name ){
    return get_intrinsics()->has_auth(name);
}

void require_auth2( capi_name name, capi_name permission ){
    get_intrinsics()->require_auth2(name, permission);
}

bool is_account( capi_name name ){
    return get_intrinsics()->is_account(name);
}

void send_inline(char *serialized_action, size_t size){
    get_intrinsics()->send_inline(serialized_action, size);
}

void send_context_free_inline(char *serialized_action, size_t size){
    get_intrinsics()->send_context_free_inline(serialized_action, size);
}

uint64_t  publication_time(){
    return get_intrinsics()->publication_time();
}

capi_name current_receiver(){
    return get_intrinsics()->current_receiver();
}

void prints( const char* cstr ){
    get_intrinsics()->prints(cstr);
}

void prints_l( const char* cstr, uint32_t len){
    get_intrinsics()->prints_l(cstr, len);
}

void printi( int64_t value ){
    get_intrinsics()->printi(value);
}

void printui( uint64_t value ){
    get_intrinsics()->printui(value);
}

void printi128( const int128_t* value ){
    get_intrinsics()->printi128(value);
}

void printui128( const uint128_t* value ){
    get_intrinsics()->printui128(value);
}

void printsf(float value){
    get_intrinsics()->printsf(value);
}

void printdf(double value){
    get_intrinsics()->printdf(value);
}

void printqf(const long double* value){
    get_intrinsics()->printqf(value);
}

void printn( uint64_t name ){
    get_intrinsics()->printn(name);
}

void printhex( const void* data, uint32_t datalen ){
    get_intrinsics()->printhex(data, datalen);
}

void  eosio_assert( uint32_t test, const char* msg ){
    get_intrinsics()->eosio_assert(test, msg);
}

void  eosio_assert_message( uint32_t test, const char* msg, uint32_t msg_len ){
    get_intrinsics()->eosio_assert_message(test, msg, msg_len);
}

void  eosio_assert_code( uint32_t test, uint64_t code ){
    get_intrinsics()->eosio_assert_code(test, code);
}

uint64_t  current_time(){
    return get_intrinsics()->current_time();
}

bool is_feature_activated( const capi_checksum256* feature_digest ){
    return get_intrinsics()->is_feature_activated(feature_digest);
}

capi_name get_sender(){
    return get_intrinsics()->get_sender();
}

void get_resource_limits( capi_name account, int64_t* ram_bytes, int64_t* net_weight, int64_t* cpu_weight ){
    get_intrinsics()->get_resource_limits(account, ram_bytes, net_weight, cpu_weight);
}

void set_resource_limits( capi_name account, int64_t ram_bytes, int64_t net_weight, int64_t cpu_weight ){
    get_intrinsics()->set_resource_limits(account, ram_bytes, net_weight, cpu_weight);
}

int64_t set_proposed_producers( char *producer_data, uint32_t producer_data_size ){
    return get_intrinsics()->set_proposed_producers(producer_data, producer_data_size);
}

int64_t set_proposed_producers_ex( uint64_t producer_data_format, char *producer_data, uint32_t producer_data_size ){
    return get_intrinsics()->set_proposed_producers_ex(producer_data_format, producer_data, producer_data_size);
}

bool is_privileged( capi_name account ){
    return get_intrinsics()->is_privileged(account);
}

void set_privileged( capi_name account, bool is_priv ){
    get_intrinsics()->set_privileged(account, is_priv);
}

void set_blockchain_parameters_packed( char* data, uint32_t datalen ){
    get_intrinsics()->set_blockchain_parameters_packed(data, datalen);
}

uint32_t get_blockchain_parameters_packed( char* data, uint32_t datalen ){
    return get_intrinsics()->get_blockchain_parameters_packed(data, datalen);
}

void preactivate_feature( const capi_checksum256* feature_digest ){
    get_intrinsics()->preactivate_feature(feature_digest);
}

void send_deferred(const uint128_t& sender_id, capi_name payer, const char *serialized_transaction, size_t size, uint32_t replace_existing){
    get_intrinsics()->send_deferred(sender_id, payer, serialized_transaction, size, 0);
}

int cancel_deferred(const uint128_t& sender_id){
    return get_intrinsics()->cancel_deferred(sender_id);
}

size_t read_transaction(char *buffer, size_t size){
    return get_intrinsics()->read_transaction(buffer, size);
}

size_t transaction_size(){
    return get_intrinsics()->transaction_size();
}

int tapos_block_num(){
    return get_intrinsics()->tapos_block_num();
}

int tapos_block_prefix(){
    return get_intrinsics()->tapos_block_prefix();
}

uint32_t expiration(){
    return get_intrinsics()->expiration();
}

int get_action( uint32_t type, uint32_t index, char* buff, size_t size ){
    return get_intrinsics()->get_action(type, index, buff, size);
}

int get_context_free_data( uint32_t index, char* buff, size_t size ){
    return get_intrinsics()->get_context_free_data(index, buff, size);
}

extern "C" void set_action_return_value(void* data, size_t size){
    get_intrinsics()->set_action_return_value(data, size);
}

static struct IntrinsicsFuncs *g_intrinsics_func;

IntrinsicsFuncs* get_intrinsics() {
    return g_intrinsics_func;
}

extern "C" __attribute__ ((visibility ("default"))) void native_init(struct IntrinsicsFuncs *fn) {
    g_intrinsics_func = fn;

    // intrinsics::set_intrinsic<intrinsics::get_active_producers>(
    //          []( capi_name* producers, uint32_t datalen ) {
    //              return get_intrinsics()->get_active_producers(producers, datalen);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_store_i64>(
    //          [](uint64_t scope, capi_name table, capi_name payer, uint64_t id,  const void* data, uint32_t len) {
    //              return get_intrinsics()->db_store_i64(scope, table, payer, id, data, len);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_update_i64>(
    //          [](int32_t iterator, capi_name payer, const void* data, uint32_t len) {
    //              get_intrinsics()->db_update_i64(iterator, payer, data, len);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_remove_i64>(
    //          [](int32_t iterator) {
    //              get_intrinsics()->db_remove_i64(iterator);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_get_i64>(
    //          [](int32_t iterator, const void* data, uint32_t len) {
    //              return get_intrinsics()->db_get_i64(iterator, (void *)data, len);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_next_i64>(
    //          [](int32_t iterator, uint64_t* primary) {
    //              return get_intrinsics()->db_next_i64(iterator, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_previous_i64>(
    //          [](int32_t iterator, uint64_t* primary) {
    //              return get_intrinsics()->db_previous_i64(iterator, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_find_i64>(
    //          [](capi_name code, uint64_t scope, capi_name table, uint64_t id) {
    //              return get_intrinsics()->db_find_i64(code, scope, table, id);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_lowerbound_i64>(
    //          [](capi_name code, uint64_t scope, capi_name table, uint64_t id) {
    //              return get_intrinsics()->db_lowerbound_i64(code, scope, table, id);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_upperbound_i64>(
    //          [](capi_name code, uint64_t scope, capi_name table, uint64_t id) {
    //              return get_intrinsics()->db_upperbound_i64(code, scope, table, id);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_end_i64>(
    //          [](capi_name code, uint64_t scope, capi_name table) {
    //              return get_intrinsics()->db_end_i64(code, scope, table);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx64_store>(
    //          [](uint64_t scope, capi_name table, capi_name payer, uint64_t id, const uint64_t* secondary) {
    //              return get_intrinsics()->db_idx64_store(scope, table, payer, id, secondary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx64_update>(
    //          [](int32_t iterator, capi_name payer, const uint64_t* secondary) {
    //              get_intrinsics()->db_idx64_update(iterator, payer, secondary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx64_remove>(
    //          [](int32_t iterator) {
    //              get_intrinsics()->db_idx64_remove(iterator);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx64_next>(
    //          [](int32_t iterator, uint64_t* primary) {
    //              return get_intrinsics()->db_idx64_next(iterator, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx64_previous>(
    //          [](int32_t iterator, uint64_t* primary) {
    //              return get_intrinsics()->db_idx64_previous(iterator, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx64_find_primary>(
    //          [](capi_name code, uint64_t scope, capi_name table, uint64_t* secondary, uint64_t primary) {
    //              return get_intrinsics()->db_idx64_find_primary(code, scope, table, secondary, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx64_find_secondary>(
    //          [](capi_name code, uint64_t scope, capi_name table, const uint64_t* secondary, uint64_t* primary) {
    //              return get_intrinsics()->db_idx64_find_secondary(code, scope, table, secondary, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx64_lowerbound>(
    //          [](capi_name code, uint64_t scope, capi_name table, uint64_t* secondary, uint64_t* primary) {
    //              return get_intrinsics()->db_idx64_lowerbound(code, scope, table, secondary, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx64_upperbound>(
    //          [](capi_name code, uint64_t scope, capi_name table, uint64_t* secondary, uint64_t* primary) {
    //              return get_intrinsics()->db_idx64_upperbound(code, scope, table, secondary, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx64_end>(
    //          [](capi_name code, uint64_t scope, capi_name table) {
    //              return get_intrinsics()->db_idx64_end(code, scope, table);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx128_store>(
    //          [](uint64_t scope, capi_name table, capi_name payer, uint64_t id, const uint128_t* secondary) {
    //              return get_intrinsics()->db_idx128_store(scope, table, payer, id, secondary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx128_update>(
    //          [](int32_t iterator, capi_name payer, const uint128_t* secondary) {
    //              get_intrinsics()->db_idx128_update(iterator, payer, secondary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx128_remove>(
    //          [](int32_t iterator) {
    //              get_intrinsics()->db_idx128_remove(iterator);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx128_next>(
    //          [](int32_t iterator, uint64_t* primary) {
    //              return get_intrinsics()->db_idx128_next(iterator, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx128_previous>(
    //          [](int32_t iterator, uint64_t* primary) {
    //              return get_intrinsics()->db_idx128_previous(iterator, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx128_find_primary>(
    //          [](capi_name code, uint64_t scope, capi_name table, uint128_t* secondary, uint64_t primary) {
    //              return get_intrinsics()->db_idx128_find_primary(code, scope, table, secondary, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx128_find_secondary>(
    //          [](capi_name code, uint64_t scope, capi_name table, const uint128_t* secondary, uint64_t* primary) {
    //              return get_intrinsics()->db_idx128_find_secondary(code, scope, table, secondary, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx128_lowerbound>(
    //          [](capi_name code, uint64_t scope, capi_name table, uint128_t* secondary, uint64_t* primary) {
    //              return get_intrinsics()->db_idx128_lowerbound(code, scope, table, secondary, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx128_upperbound>(
    //          [](capi_name code, uint64_t scope, capi_name table, uint128_t* secondary, uint64_t* primary) {
    //              return get_intrinsics()->db_idx128_upperbound(code, scope, table, secondary, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx128_end>(
    //          [](capi_name code, uint64_t scope, capi_name table) {
    //              return get_intrinsics()->db_idx128_end(code, scope, table);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx256_store>(
    //          [](uint64_t scope, capi_name table, capi_name payer, uint64_t id, const uint128_t* data, uint32_t data_len ) {
    //              return get_intrinsics()->db_idx256_store(scope, table, payer, id, data, data_len);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx256_update>(
    //          [](int32_t iterator, capi_name payer, const uint128_t* data, uint32_t data_len) {
    //              get_intrinsics()->db_idx256_update(iterator, payer, data, data_len);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx256_remove>(
    //          [](int32_t iterator) {
    //              get_intrinsics()->db_idx256_remove(iterator);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx256_next>(
    //          [](int32_t iterator, uint64_t* primary) {
    //              return get_intrinsics()->db_idx256_next(iterator, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx256_previous>(
    //          [](int32_t iterator, uint64_t* primary) {
    //              return get_intrinsics()->db_idx256_previous(iterator, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx256_find_primary>(
    //          [](capi_name code, uint64_t scope, capi_name table, uint128_t* data, uint32_t data_len, uint64_t primary) {
    //              return get_intrinsics()->db_idx256_find_primary(code, scope, table, data, data_len, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx256_find_secondary>(
    //          [](capi_name code, uint64_t scope, capi_name table, const uint128_t* data, uint32_t data_len, uint64_t* primary) {
    //              return get_intrinsics()->db_idx256_find_secondary(code, scope, table, data, data_len, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx256_lowerbound>(
    //          [](capi_name code, uint64_t scope, capi_name table, uint128_t* data, uint32_t data_len, uint64_t* primary) {
    //              return get_intrinsics()->db_idx256_lowerbound(code, scope, table, data, data_len, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx256_upperbound>(
    //          [](capi_name code, uint64_t scope, capi_name table, uint128_t* data, uint32_t data_len, uint64_t* primary) {
    //              return get_intrinsics()->db_idx256_upperbound(code, scope, table, data, data_len, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx256_end>(
    //          [](capi_name code, uint64_t scope, capi_name table) {
    //              return get_intrinsics()->db_idx256_end(code, scope, table);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_double_store>(
    //          [](uint64_t scope, capi_name table, capi_name payer, uint64_t id, const double* secondary) {
    //              return get_intrinsics()->db_idx_double_store(scope, table, payer, id, secondary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_double_update>(
    //          [](int32_t iterator, capi_name payer, const double* secondary) {
    //              get_intrinsics()->db_idx_double_update(iterator, payer, secondary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_double_remove>(
    //          [](int32_t iterator) {
    //              get_intrinsics()->db_idx_double_remove(iterator);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_double_next>(
    //          [](int32_t iterator, uint64_t* primary) {
    //              return get_intrinsics()->db_idx_double_next(iterator, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_double_previous>(
    //          [](int32_t iterator, uint64_t* primary) {
    //              return get_intrinsics()->db_idx_double_previous(iterator, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_double_find_primary>(
    //          [](capi_name code, uint64_t scope, capi_name table, double* secondary, uint64_t primary) {
    //              return get_intrinsics()->db_idx_double_find_primary(code, scope, table, secondary, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_double_find_secondary>(
    //          [](capi_name code, uint64_t scope, capi_name table, const double* secondary, uint64_t* primary) {
    //              return get_intrinsics()->db_idx_double_find_secondary(code, scope, table, secondary, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_double_lowerbound>(
    //          [](capi_name code, uint64_t scope, capi_name table, double* secondary, uint64_t* primary) {
    //              return get_intrinsics()->db_idx_double_lowerbound(code, scope, table, secondary, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_double_upperbound>(
    //          [](capi_name code, uint64_t scope, capi_name table, double* secondary, uint64_t* primary) {
    //              return get_intrinsics()->db_idx_double_upperbound(code, scope, table, secondary, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_double_end>(
    //          [](capi_name code, uint64_t scope, capi_name table) {
    //              return get_intrinsics()->db_idx_double_end(code, scope, table);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_long_double_store>(
    //          [](uint64_t scope, capi_name table, capi_name payer, uint64_t id, const long double* secondary) {
    //              return get_intrinsics()->db_idx_long_double_store(scope, table, payer, id, secondary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_long_double_update>(
    //          [](int32_t iterator, capi_name payer, const long double* secondary) {
    //              get_intrinsics()->db_idx_long_double_update(iterator, payer, secondary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_long_double_remove>(
    //          [](int32_t iterator) {
    //              get_intrinsics()->db_idx_long_double_remove(iterator);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_long_double_next>(
    //          [](int32_t iterator, uint64_t* primary) {
    //              return get_intrinsics()->db_idx_long_double_next(iterator, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_long_double_previous>(
    //          [](int32_t iterator, uint64_t* primary) {
    //              return get_intrinsics()->db_idx_long_double_previous(iterator, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_long_double_find_primary>(
    //          [](capi_name code, uint64_t scope, capi_name table, long double* secondary, uint64_t primary) {
    //              return get_intrinsics()->db_idx_long_double_find_primary(code, scope, table, secondary, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_long_double_find_secondary>(
    //          [](capi_name code, uint64_t scope, capi_name table, const long double* secondary, uint64_t* primary) {
    //              return get_intrinsics()->db_idx_long_double_find_secondary(code, scope, table, secondary, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_long_double_lowerbound>(
    //          [](capi_name code, uint64_t scope, capi_name table, long double* secondary, uint64_t* primary) {
    //              return get_intrinsics()->db_idx_long_double_lowerbound(code, scope, table, secondary, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_long_double_upperbound>(
    //          [](capi_name code, uint64_t scope, capi_name table, long double* secondary, uint64_t* primary) {
    //              return get_intrinsics()->db_idx_long_double_upperbound(code, scope, table, secondary, primary);
    //          });

    // intrinsics::set_intrinsic<intrinsics::db_idx_long_double_end>(
    //          [](capi_name code, uint64_t scope, capi_name table) {
    //              return get_intrinsics()->db_idx_long_double_end(code, scope, table);
    //          });

    // intrinsics::set_intrinsic<intrinsics::check_transaction_authorization>(
    //          []( const char* trx_data,     uint32_t trx_size, const char* pubkeys_data, uint32_t pubkeys_size,const char* perms_data,   uint32_t perms_size) {
    //              return get_intrinsics()->check_transaction_authorization(trx_data, trx_size, pubkeys_data, pubkeys_size, perms_data, perms_size);
    //          });

    // intrinsics::set_intrinsic<intrinsics::check_permission_authorization>(
    //          []( capi_name account, capi_name permission, const char* pubkeys_data, uint32_t pubkeys_size, const char* perms_data,   uint32_t perms_size, uint64_t delay_us) {
    //              return get_intrinsics()->check_permission_authorization(account, permission, pubkeys_data, pubkeys_size, perms_data, perms_size, delay_us);
    //          });

    // intrinsics::set_intrinsic<intrinsics::get_permission_last_used>(
    //          []( capi_name account, capi_name permission ) {
    //              return get_intrinsics()->get_permission_last_used(account, permission);
    //          });

    // intrinsics::set_intrinsic<intrinsics::get_account_creation_time>(
    //          []( capi_name account ) {
    //              return get_intrinsics()->get_account_creation_time(account);
    //          });

    // intrinsics::set_intrinsic<intrinsics::assert_sha256>(
    //          []( const char* data, uint32_t length, const capi_checksum256* hash ) {
    //              get_intrinsics()->assert_sha256(data, length, hash);
    //          });

    // intrinsics::set_intrinsic<intrinsics::assert_sha1>(
    //          []( const char* data, uint32_t length, const capi_checksum160* hash ) {
    //              get_intrinsics()->assert_sha1(data, length, hash);
    //          });

    // intrinsics::set_intrinsic<intrinsics::assert_sha512>(
    //          []( const char* data, uint32_t length, const capi_checksum512* hash ) {
    //              get_intrinsics()->assert_sha512(data, length, hash);
    //          });

    // intrinsics::set_intrinsic<intrinsics::assert_ripemd160>(
    //          []( const char* data, uint32_t length, const capi_checksum160* hash ) {
    //              get_intrinsics()->assert_ripemd160(data, length, hash);
    //          });

    // intrinsics::set_intrinsic<intrinsics::sha256>(
    //          []( const char* data, uint32_t length, capi_checksum256* hash ) {
    //              get_intrinsics()->sha256(data, length, hash);
    //          });

    // intrinsics::set_intrinsic<intrinsics::sha1>(
    //          []( const char* data, uint32_t length, capi_checksum160* hash ) {
    //              get_intrinsics()->sha1(data, length, hash);
    //          });

    // intrinsics::set_intrinsic<intrinsics::sha512>(
    //          []( const char* data, uint32_t length, capi_checksum512* hash ) {
    //              get_intrinsics()->sha512(data, length, hash);
    //          });

    // intrinsics::set_intrinsic<intrinsics::ripemd160>(
    //          []( const char* data, uint32_t length, capi_checksum160* hash ) {
    //              get_intrinsics()->ripemd160(data, length, hash);
    //          });

    // intrinsics::set_intrinsic<intrinsics::recover_key>(
    //          []( const capi_checksum256* digest, const char* sig, size_t siglen, char* pub, size_t publen ) {
    //              return get_intrinsics()->recover_key(digest, sig, siglen, pub, publen);
    //          });

    // intrinsics::set_intrinsic<intrinsics::assert_recover_key>(
    //          []( const capi_checksum256* digest, const char* sig, size_t siglen, const char* pub, size_t publen ) {
    //              get_intrinsics()->assert_recover_key(digest, sig, siglen, pub, publen);
    //          });

    // intrinsics::set_intrinsic<intrinsics::read_action_data>(
    //          []( void* msg, uint32_t len ) {
    //              return get_intrinsics()->read_action_data(msg, len);
    //          });

    // intrinsics::set_intrinsic<intrinsics::action_data_size>(
    //          []() {
    //              return get_intrinsics()->action_data_size();
    //          });

    // intrinsics::set_intrinsic<intrinsics::require_recipient>(
    //          []( capi_name name ) {
    //              get_intrinsics()->require_recipient(name);
    //          });

    // intrinsics::set_intrinsic<intrinsics::require_auth>(
    //          []( capi_name name ) {
    //              get_intrinsics()->require_auth(name);
    //          });

    // intrinsics::set_intrinsic<intrinsics::has_auth>(
    //          []( capi_name name ) {
    //              return get_intrinsics()->has_auth(name);
    //          });

    // intrinsics::set_intrinsic<intrinsics::require_auth2>(
    //          []( capi_name name, capi_name permission ) {
    //              get_intrinsics()->require_auth2(name, permission);
    //          });

    // intrinsics::set_intrinsic<intrinsics::is_account>(
    //          []( capi_name name ) {
    //              return get_intrinsics()->is_account(name);
    //          });

    // intrinsics::set_intrinsic<intrinsics::send_inline>(
    //          [](char *serialized_action, size_t size) {
    //              get_intrinsics()->send_inline(serialized_action, size);
    //          });

    // intrinsics::set_intrinsic<intrinsics::send_context_free_inline>(
    //          [](char *serialized_action, size_t size) {
    //              get_intrinsics()->send_context_free_inline(serialized_action, size);
    //          });

    // intrinsics::set_intrinsic<intrinsics::publication_time>(
    //          []() {
    //              return get_intrinsics()->publication_time();
    //          });

    // intrinsics::set_intrinsic<intrinsics::current_receiver>(
    //          []() {
    //              return get_intrinsics()->current_receiver();
    //          });

    // intrinsics::set_intrinsic<intrinsics::prints>(
    //          []( const char* cstr ) {
    //              get_intrinsics()->prints(cstr);
    //          });


    // intrinsics::set_intrinsic<intrinsics::prints_l>(
    //          []( const char* cstr, uint32_t len) {
    //              get_intrinsics()->prints_l(cstr, len);
    //          });

    // intrinsics::set_intrinsic<intrinsics::printi>(
    //          []( int64_t value ) {
    //              get_intrinsics()->printi(value);
    //          });

    // intrinsics::set_intrinsic<intrinsics::printui>(
    //          []( uint64_t value ) {
    //              get_intrinsics()->printui(value);
    //          });

    // intrinsics::set_intrinsic<intrinsics::printi128>(
    //          []( const int128_t* value ) {
    //              get_intrinsics()->printi128(value);
    //          });

    // intrinsics::set_intrinsic<intrinsics::printui128>(
    //          []( const uint128_t* value ) {
    //              get_intrinsics()->printui128(value);
    //          });

    // intrinsics::set_intrinsic<intrinsics::printsf>(
    //          [](float value) {
    //              get_intrinsics()->printsf(value);
    //          });

    // intrinsics::set_intrinsic<intrinsics::printdf>(
    //          [](double value) {
    //              get_intrinsics()->printdf(value);
    //          });

    // intrinsics::set_intrinsic<intrinsics::printqf>(
    //          [](const long double* value) {
    //              get_intrinsics()->printqf(value);
    //          });

    // intrinsics::set_intrinsic<intrinsics::printn>(
    //          []( uint64_t name ) {
    //              get_intrinsics()->printn(name);
    //          });

    // intrinsics::set_intrinsic<intrinsics::printhex>(
    //          []( const void* data, uint32_t datalen ) {
    //              get_intrinsics()->printhex(data, datalen);
    //          });

    // intrinsics::set_intrinsic<intrinsics::eosio_assert>(
    //          []( uint32_t test, const char* msg ) {
    //              get_intrinsics()->eosio_assert(test, msg);
    //          });

    // intrinsics::set_intrinsic<intrinsics::eosio_assert_message>(
    //          []( uint32_t test, const char* msg, uint32_t msg_len ) {
    //              get_intrinsics()->eosio_assert_message(test, msg, msg_len);
    //          });

    // intrinsics::set_intrinsic<intrinsics::eosio_assert_code>(
    //          []( uint32_t test, uint64_t code ) {
    //              get_intrinsics()->eosio_assert_code(test, code);
    //          });

    // intrinsics::set_intrinsic<intrinsics::current_time>(
    //          []() {
    //              return get_intrinsics()->current_time();
    //          });

    // intrinsics::set_intrinsic<intrinsics::is_feature_activated>(
    //          []( const capi_checksum256* feature_digest ) {
    //              return get_intrinsics()->is_feature_activated(feature_digest);
    //          });

    // intrinsics::set_intrinsic<intrinsics::get_sender>(
    //          []() {
    //              return get_intrinsics()->get_sender();
    //          });

    // intrinsics::set_intrinsic<intrinsics::get_resource_limits>(
    //          []( capi_name account, int64_t* ram_bytes, int64_t* net_weight, int64_t* cpu_weight ) {
    //              get_intrinsics()->get_resource_limits(account, ram_bytes, net_weight, cpu_weight);
    //          });

    // intrinsics::set_intrinsic<intrinsics::set_resource_limits>(
    //          []( capi_name account, int64_t ram_bytes, int64_t net_weight, int64_t cpu_weight ) {
    //              get_intrinsics()->set_resource_limits(account, ram_bytes, net_weight, cpu_weight);
    //          });

    // intrinsics::set_intrinsic<intrinsics::set_proposed_producers>(
    //          []( char *producer_data, uint32_t producer_data_size ) {
    //              return get_intrinsics()->set_proposed_producers(producer_data, producer_data_size);
    //          });

    // intrinsics::set_intrinsic<intrinsics::set_proposed_producers_ex>(
    //          []( uint64_t producer_data_format, char *producer_data, uint32_t producer_data_size ) {
    //              return get_intrinsics()->set_proposed_producers_ex(producer_data_format, producer_data, producer_data_size);
    //          });

    // intrinsics::set_intrinsic<intrinsics::is_privileged>(
    //          []( capi_name account ) {
    //              return get_intrinsics()->is_privileged(account);
    //          });

    // intrinsics::set_intrinsic<intrinsics::set_privileged>(
    //          []( capi_name account, bool is_priv ) {
    //              get_intrinsics()->set_privileged(account, is_priv);
    //          });

    // intrinsics::set_intrinsic<intrinsics::set_blockchain_parameters_packed>(
    //          []( char* data, uint32_t datalen ) {
    //              get_intrinsics()->set_blockchain_parameters_packed(data, datalen);
    //          });

    // intrinsics::set_intrinsic<intrinsics::get_blockchain_parameters_packed>(
    //          []( char* data, uint32_t datalen ) {
    //              return get_intrinsics()->get_blockchain_parameters_packed(data, datalen);
    //          });

    // intrinsics::set_intrinsic<intrinsics::preactivate_feature>(
    //          []( const capi_checksum256* feature_digest ) {
    //              get_intrinsics()->preactivate_feature(feature_digest);
    //          });

    // intrinsics::set_intrinsic<intrinsics::send_deferred>(
    //          [](const uint128_t& sender_id, capi_name payer, const char *serialized_transaction, size_t size, uint32_t replace_existing = 0) {
    //              get_intrinsics()->send_deferred(sender_id, payer, serialized_transaction, size, 0);
    //          });

    // intrinsics::set_intrinsic<intrinsics::cancel_deferred>(
    //          [](const uint128_t& sender_id) {
    //              return get_intrinsics()->cancel_deferred(sender_id);
    //          });

    // intrinsics::set_intrinsic<intrinsics::read_transaction>(
    //          [](char *buffer, size_t size) {
    //              return get_intrinsics()->read_transaction(buffer, size);
    //          });

    // intrinsics::set_intrinsic<intrinsics::transaction_size>(
    //          []() {
    //              return get_intrinsics()->transaction_size();
    //          });

    // intrinsics::set_intrinsic<intrinsics::tapos_block_num>(
    //          []() {
    //              return get_intrinsics()->tapos_block_num();
    //          });

    // intrinsics::set_intrinsic<intrinsics::tapos_block_prefix>(
    //          []() {
    //              return get_intrinsics()->tapos_block_prefix();
    //          });

    // intrinsics::set_intrinsic<intrinsics::expiration>(
    //          []() {
    //              return get_intrinsics()->expiration();
    //          });

    // intrinsics::set_intrinsic<intrinsics::get_action>(
    //          []( uint32_t type, uint32_t index, char* buff, size_t size ) {
    //              return get_intrinsics()->get_action(type, index, buff, size);
    //          });

    // intrinsics::set_intrinsic<intrinsics::get_context_free_data>(
    //          []( uint32_t index, char* buff, size_t size ) {
    //              return get_intrinsics()->get_context_free_data(index, buff, size);
    //          });

    // intrinsics::set_intrinsic<intrinsics::set_action_return_value>(
    //          [](void* data, size_t size) {
    //              get_intrinsics()->set_action_return_value(data, size);
    //          });
}

extern "C" int main(int argc, char **argv) {
    return 0;
}
