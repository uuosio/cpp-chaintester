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
int32_t db_store_i64(uint64_t scope, capi_name table, capi_name payer, uint64_t id,  const void* data, uint32_t len) {
    return GetApplyClient()->db_store_i64(
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(payer),
        to_raw_uint64(id),
        string((char *)data, len)
    );
}

void db_update_i64(int32_t iterator, capi_name payer, const void* data, uint32_t len) {
    GetApplyClient()->db_update_i64(iterator, to_raw_uint64(payer), string((char *)data, len));
}

void db_remove_i64(int32_t iterator) {
    GetApplyClient()->db_remove_i64(iterator);
}

size_t copy_data(void* dest, size_t dest_len, string& src) {
    if (dest_len == 0) {
        return src.size();
    }
    size_t copy_size = std::min(dest_len, src.size());
    memcpy(dest, src.c_str(), copy_size);
    return copy_size;
}

int32_t db_get_i64(int32_t iterator, const void* data, uint32_t len) {
    string ret;
    GetApplyClient()->db_get_i64(ret, iterator);
    return copy_data((void *)data, len, ret);
}

int32_t db_next_i64(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_next_i64(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_previous_i64(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_previous_i64(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_find_i64(capi_name code, uint64_t scope, capi_name table, uint64_t id) {
    return GetApplyClient()->db_find_i64(
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(id)
    );
}

int32_t db_lowerbound_i64(capi_name code, uint64_t scope, capi_name table, uint64_t id) {
    return GetApplyClient()->db_lowerbound_i64(
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(id)
    );
}

int32_t db_upperbound_i64(capi_name code, uint64_t scope, capi_name table, uint64_t id) {
    return GetApplyClient()->db_upperbound_i64(
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(id)
    );
}

int32_t db_end_i64(capi_name code, uint64_t scope, capi_name table) {
    return GetApplyClient()->db_end_i64(
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table)
    );
}

int32_t db_idx64_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const uint64_t* secondary) {
    return GetApplyClient()->db_idx64_store(
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(payer),
        to_raw_uint64(id),
        to_raw_uint64(*secondary)
    );
}

void db_idx64_update(int32_t iterator, capi_name payer, const uint64_t* secondary) {
    GetApplyClient()->db_idx64_update(iterator, to_raw_uint64(payer), to_raw_uint64(*secondary));    
}

void db_idx64_remove(int32_t iterator) {
    GetApplyClient()->db_idx64_remove(iterator);    
}

int32_t db_idx64_next(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx64_next(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx64_previous(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx64_previous(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx64_find_primary(capi_name code, uint64_t scope, capi_name table, uint64_t* secondary, uint64_t primary) {
    FindPrimaryReturn ret;
    GetApplyClient()->db_idx64_find_primary(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(primary)

    );
    if (ret.iterator >= 0) {
        if (ret.secondary.size() != 8) {
            throw std::runtime_error("db_idx64_find_primary: bad secondary return size");
        }
        memcpy(secondary, ret.secondary.c_str(), 8);
    }
    return ret.iterator;
}

int32_t db_idx64_find_secondary(capi_name code, uint64_t scope, capi_name table, const uint64_t* secondary, uint64_t* primary) {
    FindSecondaryReturn ret;
    GetApplyClient()->db_idx64_find_secondary(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(*secondary)
    );

    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx64_lowerbound(capi_name code, uint64_t scope, capi_name table, uint64_t* secondary, uint64_t* primary) {
    LowerBoundUpperBoundReturn ret;
    GetApplyClient()->db_idx64_lowerbound(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(*secondary),
        to_raw_uint64(*primary)
    );
    if (ret.iterator >= 0) {
        if (ret.secondary.size() != 8) {
            throw std::runtime_error("db_idx64_lowerbound: bad secondary return size");
        }
        memcpy(secondary, ret.secondary.c_str(), 8);
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx64_upperbound(capi_name code, uint64_t scope, capi_name table, uint64_t* secondary, uint64_t* primary) {
    LowerBoundUpperBoundReturn ret;
    GetApplyClient()->db_idx64_upperbound(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(*secondary),
        to_raw_uint64(*primary)
    );
    if (ret.iterator >= 0) {
        if (ret.secondary.size() != 8) {
            throw std::runtime_error("db_idx64_upperbound: bad secondary return size");
        }
        memcpy(secondary, ret.secondary.c_str(), 8);
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx64_end(capi_name code, uint64_t scope, capi_name table) {
    return GetApplyClient()->db_idx64_end(
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table)
    );
}

int32_t db_idx128_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const uint128_t* secondary) {
    return GetApplyClient()->db_idx128_store(
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(payer),
        to_raw_uint64(id),
        string((char *)secondary, 16)
    );    
}

void db_idx128_update(int32_t iterator, capi_name payer, const uint128_t* secondary) {
    GetApplyClient()->db_idx128_update(iterator, to_raw_uint64(payer), string((char *)secondary, 16));
}

void db_idx128_remove(int32_t iterator) {
    GetApplyClient()->db_idx128_remove(iterator);    
}

int32_t db_idx128_next(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx128_next(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx128_previous(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx128_previous(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx128_find_primary(capi_name code, uint64_t scope, capi_name table, uint128_t* secondary, uint64_t primary) {
    FindPrimaryReturn ret;
    GetApplyClient()->db_idx128_find_primary(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(primary)

    );
    if (ret.iterator >= 0) {
        if (ret.secondary.size() != 16) {
            throw std::runtime_error("db_idx128_find_primary: bad secondary return size");
        }
        memcpy(secondary, ret.secondary.c_str(), 16);
    }
    return ret.iterator;
}

int32_t db_idx128_find_secondary(capi_name code, uint64_t scope, capi_name table, const uint128_t* secondary, uint64_t* primary) {
    FindSecondaryReturn ret;
    GetApplyClient()->db_idx128_find_secondary(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        string((char *)secondary, 16)
    );

    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;

}

int32_t db_idx128_lowerbound(capi_name code, uint64_t scope, capi_name table, uint128_t* secondary, uint64_t* primary) {
    LowerBoundUpperBoundReturn ret;
    GetApplyClient()->db_idx128_lowerbound(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        string((char *)secondary, 16),
        to_raw_uint64(*primary)
    );
    if (ret.iterator >= 0) {
        if (ret.secondary.size() != 16) {
            throw std::runtime_error("db_idx128_lowerbound: bad secondary return size");
        }
        memcpy(secondary, ret.secondary.c_str(), 16);
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx128_upperbound(capi_name code, uint64_t scope, capi_name table, uint128_t* secondary, uint64_t* primary) {
    LowerBoundUpperBoundReturn ret;
    GetApplyClient()->db_idx128_upperbound(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        string((char *)secondary, 16),
        to_raw_uint64(*primary)
    );
    if (ret.iterator >= 0) {
        if (ret.secondary.size() != 16) {
            throw std::runtime_error("db_idx128_upperbound: bad secondary return size");
        }
        memcpy(secondary, ret.secondary.c_str(), 16);
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx128_end(capi_name code, uint64_t scope, capi_name table) {
    return GetApplyClient()->db_idx128_end(
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table)
    );
}

int32_t db_idx256_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const uint128_t* data, uint32_t data_len ) {
    if (data_len != 2) {
        throw std::runtime_error("db_idx256_store: bad data length");
    }
    return GetApplyClient()->db_idx256_store(
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(payer),
        to_raw_uint64(id),
        string((char *)data, 32)
    );    
}

void db_idx256_update(int32_t iterator, capi_name payer, const uint128_t* data, uint32_t data_len) {
    if (data_len != 2) {
        throw std::runtime_error("db_idx256_store: bad data length");
    }
    GetApplyClient()->db_idx256_update(iterator, to_raw_uint64(payer), string((char *)data, 32));    
}

void db_idx256_remove(int32_t iterator) {
    GetApplyClient()->db_idx256_remove(iterator);    
}

int32_t db_idx256_next(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx256_next(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx256_previous(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx256_previous(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx256_find_primary(capi_name code, uint64_t scope, capi_name table, uint128_t* data, uint32_t data_len, uint64_t primary) {
    FindPrimaryReturn ret;
    if (data_len != 2) {
        throw std::runtime_error("db_idx256_find_primary: bad data length");
    }
    GetApplyClient()->db_idx256_find_primary(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(primary)
    );
    if (ret.iterator >= 0) {
        if (ret.secondary.size() != 32) {
            throw std::runtime_error("db_idx256_find_primary: bad secondary return size");
        }
        memcpy(data, ret.secondary.c_str(), 32);
    }
    return ret.iterator;
}

int32_t db_idx256_find_secondary(capi_name code, uint64_t scope, capi_name table, const uint128_t* data, uint32_t data_len, uint64_t* primary) {
    FindSecondaryReturn ret;
    if (data_len != 2) {
        throw std::runtime_error("db_idx256_find_secondary: bad data length");
    }
    GetApplyClient()->db_idx256_find_secondary(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        string((char *)data, 32)
    );

    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx256_lowerbound(capi_name code, uint64_t scope, capi_name table, uint128_t* data, uint32_t data_len, uint64_t* primary) {
    LowerBoundUpperBoundReturn ret;
    if (data_len != 2) {
        throw std::runtime_error("db_idx256_lowerbound: bad data length");
    }
    GetApplyClient()->db_idx256_lowerbound(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        string((char *)data, 32),
        to_raw_uint64(*primary)
    );
    if (ret.iterator >= 0) {
        if (ret.secondary.size() != 32) {
            throw std::runtime_error("db_idx256_lowerbound: bad secondary return size");
        }
        memcpy(data, ret.secondary.c_str(), 32);
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx256_upperbound(capi_name code, uint64_t scope, capi_name table, uint128_t* data, uint32_t data_len, uint64_t* primary) {
    LowerBoundUpperBoundReturn ret;
    if (data_len != 2) {
        throw std::runtime_error("db_idx256_upperbound: bad data length");
    }
    GetApplyClient()->db_idx256_upperbound(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        string((char *)data, 32),
        to_raw_uint64(*primary)
    );
    if (ret.iterator >= 0) {
        if (ret.secondary.size() != 32) {
            throw std::runtime_error("db_idx256_upperbound: bad secondary return size");
        }
        memcpy(data, ret.secondary.c_str(), 32);
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx256_end(capi_name code, uint64_t scope, capi_name table) {
    return GetApplyClient()->db_idx256_end(
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table)
    );
}

int32_t db_idx_double_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const double* secondary) {
    return GetApplyClient()->db_idx_double_store(
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(payer),
        to_raw_uint64(id),
        string((char *)secondary, 8)
    );
}

void db_idx_double_update(int32_t iterator, capi_name payer, const double* secondary) {
    GetApplyClient()->db_idx_double_update(iterator, to_raw_uint64(payer), string((char *)secondary, 8));    
}

void db_idx_double_remove(int32_t iterator) {
    GetApplyClient()->db_idx_double_remove(iterator);    
}

int32_t db_idx_double_next(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx_double_next(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;    
}

int32_t db_idx_double_previous(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx_double_previous(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx_double_find_primary(capi_name code, uint64_t scope, capi_name table, double* secondary, uint64_t primary) {
    FindPrimaryReturn ret;
    GetApplyClient()->db_idx_double_find_primary(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(primary)

    );
    if (ret.iterator >= 0) {
        memcpy(secondary, ret.secondary.c_str(), ret.secondary.size());
    }
    return ret.iterator;
}

int32_t db_idx_double_find_secondary(capi_name code, uint64_t scope, capi_name table, const double* secondary, uint64_t* primary) {
    FindSecondaryReturn ret;
    GetApplyClient()->db_idx_double_find_secondary(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        string((char *)secondary, 8)
    );

    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx_double_lowerbound(capi_name code, uint64_t scope, capi_name table, double* secondary, uint64_t* primary) {
    LowerBoundUpperBoundReturn ret;
    GetApplyClient()->db_idx_double_lowerbound(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        string((char *)secondary, 8),
        to_raw_uint64(*primary)
    );
    if (ret.iterator >= 0) {
        memcpy(secondary, ret.secondary.c_str(), 8);
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx_double_upperbound(capi_name code, uint64_t scope, capi_name table, double* secondary, uint64_t* primary) {
    LowerBoundUpperBoundReturn ret;
    GetApplyClient()->db_idx_double_upperbound(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        string((char *)secondary, 8),
        to_raw_uint64(*primary)
    );
    if (ret.iterator >= 0) {
        memcpy(secondary, ret.secondary.c_str(), 8);
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx_double_end(capi_name code, uint64_t scope, capi_name table) {
    return GetApplyClient()->db_idx_double_end(
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table)
    );
}

int32_t db_idx_long_double_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const long double* secondary) {
    return GetApplyClient()->db_idx_long_double_store(
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(payer),
        to_raw_uint64(id),
        string((char *)secondary, 16)
    );    
}

void db_idx_long_double_update(int32_t iterator, capi_name payer, const long double* secondary) {
    GetApplyClient()->db_idx_long_double_update(iterator, to_raw_uint64(payer), string((char *)secondary, 16));    
}

void db_idx_long_double_remove(int32_t iterator) {
    GetApplyClient()->db_idx_long_double_remove(iterator);    
}

int32_t db_idx_long_double_next(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx_long_double_next(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;    
}

int32_t db_idx_long_double_previous(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx_long_double_previous(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx_long_double_find_primary(capi_name code, uint64_t scope, capi_name table, long double* secondary, uint64_t primary) {
    FindPrimaryReturn ret;
    GetApplyClient()->db_idx_long_double_find_primary(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(primary)

    );
    if (ret.iterator >= 0) {
        memcpy(secondary, ret.secondary.c_str(), ret.secondary.size());
    }
    return ret.iterator;
}

int32_t db_idx_long_double_find_secondary(capi_name code, uint64_t scope, capi_name table, const long double* secondary, uint64_t* primary) {
    FindSecondaryReturn ret;
    GetApplyClient()->db_idx_long_double_find_secondary(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        string((char *)secondary, 16)
    );

    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;

}

int32_t db_idx_long_double_lowerbound(capi_name code, uint64_t scope, capi_name table, long double* secondary, uint64_t* primary) {
    LowerBoundUpperBoundReturn ret;
    GetApplyClient()->db_idx_long_double_lowerbound(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        string((char *)secondary, 16),
        to_raw_uint64(*primary)
    );
    if (ret.iterator >= 0) {
        memcpy(secondary, ret.secondary.c_str(), 16);
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx_long_double_upperbound(capi_name code, uint64_t scope, capi_name table, long double* secondary, uint64_t* primary) {
    LowerBoundUpperBoundReturn ret;
    GetApplyClient()->db_idx_long_double_upperbound(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        string((char *)secondary, 16),
        to_raw_uint64(*primary)
    );
    if (ret.iterator >= 0) {
        memcpy(secondary, ret.secondary.c_str(), 16);
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

int32_t db_idx_long_double_end(capi_name code, uint64_t scope, capi_name table) {
    return GetApplyClient()->db_idx_long_double_end(
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table)
    );
}

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
    if (test) {
        return;
    }
    GetApplyClient()->eosio_assert(0, string(msg));
}

void  eosio_assert_message( uint32_t test, const char* msg, uint32_t msg_len ) {
    if (test) {
        return;
    }
    GetApplyClient()->eosio_assert_message(0, string(msg, msg_len));
}

void  eosio_assert_code( uint32_t test, uint64_t code ) {
    if (test) {
        return;
    }
    GetApplyClient()->eosio_assert_code(0, to_raw_uint64(code));
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

void set_action_return_value(void* data, size_t size) {

}

static bool initialized = false;
static struct IntrinsicsFuncs g_intrinsics_func;

IntrinsicsFuncs* get_intrinsics() {
    if (!initialized) {
        init_intrinsics();
        initialized = true;
    }
    return &g_intrinsics_func;
}

void init_intrinsics() {
    g_intrinsics_func.get_active_producers = get_active_producers;
    g_intrinsics_func.db_store_i64 = db_store_i64;
    g_intrinsics_func.db_update_i64 = db_update_i64;
    g_intrinsics_func.db_remove_i64 = db_remove_i64;
    g_intrinsics_func.db_get_i64 = db_get_i64;
    g_intrinsics_func.db_next_i64 = db_next_i64;
    g_intrinsics_func.db_previous_i64 = db_previous_i64;
    g_intrinsics_func.db_find_i64 = db_find_i64;
    g_intrinsics_func.db_lowerbound_i64 = db_lowerbound_i64;
    g_intrinsics_func.db_upperbound_i64 = db_upperbound_i64;
    g_intrinsics_func.db_end_i64 = db_end_i64;
    g_intrinsics_func.db_idx64_store = db_idx64_store;
    g_intrinsics_func.db_idx64_update = db_idx64_update;
    g_intrinsics_func.db_idx64_remove = db_idx64_remove;
    g_intrinsics_func.db_idx64_next = db_idx64_next;
    g_intrinsics_func.db_idx64_previous = db_idx64_previous;
    g_intrinsics_func.db_idx64_find_primary = db_idx64_find_primary;
    g_intrinsics_func.db_idx64_find_secondary = db_idx64_find_secondary;
    g_intrinsics_func.db_idx64_lowerbound = db_idx64_lowerbound;
    g_intrinsics_func.db_idx64_upperbound = db_idx64_upperbound;
    g_intrinsics_func.db_idx64_end = db_idx64_end;
    g_intrinsics_func.db_idx128_store = db_idx128_store;
    g_intrinsics_func.db_idx128_update = db_idx128_update;
    g_intrinsics_func.db_idx128_remove = db_idx128_remove;
    g_intrinsics_func.db_idx128_next = db_idx128_next;
    g_intrinsics_func.db_idx128_previous = db_idx128_previous;
    g_intrinsics_func.db_idx128_find_primary = db_idx128_find_primary;
    g_intrinsics_func.db_idx128_find_secondary = db_idx128_find_secondary;
    g_intrinsics_func.db_idx128_lowerbound = db_idx128_lowerbound;
    g_intrinsics_func.db_idx128_upperbound = db_idx128_upperbound;
    g_intrinsics_func.db_idx128_end = db_idx128_end;
    g_intrinsics_func.db_idx256_store = db_idx256_store;
    g_intrinsics_func.db_idx256_update = db_idx256_update;
    g_intrinsics_func.db_idx256_remove = db_idx256_remove;
    g_intrinsics_func.db_idx256_next = db_idx256_next;
    g_intrinsics_func.db_idx256_previous = db_idx256_previous;
    g_intrinsics_func.db_idx256_find_primary = db_idx256_find_primary;
    g_intrinsics_func.db_idx256_find_secondary = db_idx256_find_secondary;
    g_intrinsics_func.db_idx256_lowerbound = db_idx256_lowerbound;
    g_intrinsics_func.db_idx256_upperbound = db_idx256_upperbound;
    g_intrinsics_func.db_idx256_end = db_idx256_end;
    g_intrinsics_func.db_idx_double_store = db_idx_double_store;
    g_intrinsics_func.db_idx_double_update = db_idx_double_update;
    g_intrinsics_func.db_idx_double_remove = db_idx_double_remove;
    g_intrinsics_func.db_idx_double_next = db_idx_double_next;
    g_intrinsics_func.db_idx_double_previous = db_idx_double_previous;
    g_intrinsics_func.db_idx_double_find_primary = db_idx_double_find_primary;
    g_intrinsics_func.db_idx_double_find_secondary = db_idx_double_find_secondary;
    g_intrinsics_func.db_idx_double_lowerbound = db_idx_double_lowerbound;
    g_intrinsics_func.db_idx_double_upperbound = db_idx_double_upperbound;
    g_intrinsics_func.db_idx_double_end = db_idx_double_end;
    g_intrinsics_func.db_idx_long_double_store = db_idx_long_double_store;
    g_intrinsics_func.db_idx_long_double_update = db_idx_long_double_update;
    g_intrinsics_func.db_idx_long_double_remove = db_idx_long_double_remove;
    g_intrinsics_func.db_idx_long_double_next = db_idx_long_double_next;
    g_intrinsics_func.db_idx_long_double_previous = db_idx_long_double_previous;
    g_intrinsics_func.db_idx_long_double_find_primary = db_idx_long_double_find_primary;
    g_intrinsics_func.db_idx_long_double_find_secondary = db_idx_long_double_find_secondary;
    g_intrinsics_func.db_idx_long_double_lowerbound = db_idx_long_double_lowerbound;
    g_intrinsics_func.db_idx_long_double_upperbound = db_idx_long_double_upperbound;
    g_intrinsics_func.db_idx_long_double_end = db_idx_long_double_end;
    g_intrinsics_func.check_transaction_authorization = check_transaction_authorization;
    g_intrinsics_func.check_permission_authorization = check_permission_authorization;
    g_intrinsics_func.get_permission_last_used = get_permission_last_used;
    g_intrinsics_func.get_account_creation_time = get_account_creation_time;
    g_intrinsics_func.assert_sha256 = assert_sha256;
    g_intrinsics_func.assert_sha1 = assert_sha1;
    g_intrinsics_func.assert_sha512 = assert_sha512;
    g_intrinsics_func.assert_ripemd160 = assert_ripemd160;
    g_intrinsics_func.sha256 = sha256;
    g_intrinsics_func.sha1 = sha1;
    g_intrinsics_func.sha512 = sha512;
    g_intrinsics_func.ripemd160 = ripemd160;
    g_intrinsics_func.recover_key = recover_key;
    g_intrinsics_func.assert_recover_key = assert_recover_key;
    g_intrinsics_func.read_action_data = read_action_data;
    g_intrinsics_func.action_data_size = action_data_size;
    g_intrinsics_func.require_recipient = require_recipient;
    g_intrinsics_func.require_auth = require_auth;
    g_intrinsics_func.has_auth = has_auth;
    g_intrinsics_func.require_auth2 = require_auth2;
    g_intrinsics_func.is_account = is_account;
    g_intrinsics_func.send_inline = send_inline;
    g_intrinsics_func.send_context_free_inline = send_context_free_inline;
    g_intrinsics_func.publication_time = publication_time;
    g_intrinsics_func.current_receiver = current_receiver;
    g_intrinsics_func.prints = prints;
    g_intrinsics_func.prints_l = prints_l;
    g_intrinsics_func.printi = printi;
    g_intrinsics_func.printui = printui;
    g_intrinsics_func.printi128 = printi128;
    g_intrinsics_func.printui128 = printui128;
    g_intrinsics_func.printsf = printsf;
    g_intrinsics_func.printdf = printdf;
    g_intrinsics_func.printqf = printqf;
    g_intrinsics_func.printn = printn;
    g_intrinsics_func.printhex = printhex;
    g_intrinsics_func.eosio_assert = eosio_assert;
    g_intrinsics_func.eosio_assert_message = eosio_assert_message;
    g_intrinsics_func.eosio_assert_code = eosio_assert_code;
    g_intrinsics_func.current_time = current_time;
    g_intrinsics_func.is_feature_activated = is_feature_activated;
    g_intrinsics_func.get_sender = get_sender;
    g_intrinsics_func.get_resource_limits = get_resource_limits;
    g_intrinsics_func.set_resource_limits = set_resource_limits;
    g_intrinsics_func.set_proposed_producers = set_proposed_producers;
    g_intrinsics_func.set_proposed_producers_ex = set_proposed_producers_ex;
    g_intrinsics_func.is_privileged = is_privileged;
    g_intrinsics_func.set_privileged = set_privileged;
    g_intrinsics_func.set_blockchain_parameters_packed = set_blockchain_parameters_packed;
    g_intrinsics_func.get_blockchain_parameters_packed = get_blockchain_parameters_packed;
    g_intrinsics_func.preactivate_feature = preactivate_feature;
    g_intrinsics_func.send_deferred = send_deferred;
    g_intrinsics_func.cancel_deferred = cancel_deferred;
    g_intrinsics_func.read_transaction = read_transaction;
    g_intrinsics_func.transaction_size = transaction_size;
    g_intrinsics_func.tapos_block_num = tapos_block_num;
    g_intrinsics_func.tapos_block_prefix = tapos_block_prefix;
    g_intrinsics_func.expiration = expiration;
    g_intrinsics_func.get_action = get_action;
    g_intrinsics_func.get_context_free_data = get_context_free_data;
    g_intrinsics_func.set_action_return_value = set_action_return_value;

}