#include <string.h>
#include <softfloat.hpp>
#include <intrinsics.h>

#include "gen/IPCChainTester.h"
#include "gen/Apply.h"
#include "gen/ApplyRequest.h"

#include "chaintester.h"

using namespace ::chaintester;

extern "C" void extF80M_to_f128M( const extFloat80_t *, float128_t * );

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

static uint32_t _get_active_producers( capi_name* producers, uint32_t datalen ) {
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
static int32_t _db_store_i64(uint64_t scope, capi_name table, capi_name payer, uint64_t id,  const void* data, uint32_t len) {
    return GetApplyClient()->db_store_i64(
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(payer),
        to_raw_uint64(id),
        string((char *)data, len)
    );
}

static void _db_update_i64(int32_t iterator, capi_name payer, const void* data, uint32_t len) {
    GetApplyClient()->db_update_i64(iterator, to_raw_uint64(payer), string((char *)data, len));
}

static void _db_remove_i64(int32_t iterator) {
    GetApplyClient()->db_remove_i64(iterator);
}

static size_t copy_data(void* dest, size_t dest_len, string& src) {
    if (dest_len == 0) {
        return src.size();
    }
    size_t copy_size = std::min(dest_len, src.size());
    memcpy(dest, src.c_str(), copy_size);
    return copy_size;
}

static int32_t _db_get_i64(int32_t iterator, const void* data, uint32_t len) {
    string ret;
    GetApplyClient()->db_get_i64(ret, iterator);
    return copy_data((void *)data, len, ret);
}

static int32_t _db_next_i64(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_next_i64(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

static int32_t _db_previous_i64(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_previous_i64(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

static int32_t _db_find_i64(capi_name code, uint64_t scope, capi_name table, uint64_t id) {
    return GetApplyClient()->db_find_i64(
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(id)
    );
}

static int32_t _db_lowerbound_i64(capi_name code, uint64_t scope, capi_name table, uint64_t id) {
    return GetApplyClient()->db_lowerbound_i64(
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(id)
    );
}

static int32_t _db_upperbound_i64(capi_name code, uint64_t scope, capi_name table, uint64_t id) {
    return GetApplyClient()->db_upperbound_i64(
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(id)
    );
}

static int32_t _db_end_i64(capi_name code, uint64_t scope, capi_name table) {
    return GetApplyClient()->db_end_i64(
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table)
    );
}

static int32_t _db_idx64_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const uint64_t* secondary) {
    return GetApplyClient()->db_idx64_store(
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(payer),
        to_raw_uint64(id),
        to_raw_uint64(*secondary)
    );
}

static void _db_idx64_update(int32_t iterator, capi_name payer, const uint64_t* secondary) {
    GetApplyClient()->db_idx64_update(iterator, to_raw_uint64(payer), to_raw_uint64(*secondary));    
}

static void _db_idx64_remove(int32_t iterator) {
    GetApplyClient()->db_idx64_remove(iterator);    
}

static int32_t _db_idx64_next(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx64_next(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

static int32_t _db_idx64_previous(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx64_previous(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

static int32_t _db_idx64_find_primary(capi_name code, uint64_t scope, capi_name table, uint64_t* secondary, uint64_t primary) {
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

static int32_t _db_idx64_find_secondary(capi_name code, uint64_t scope, capi_name table, const uint64_t* secondary, uint64_t* primary) {
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

static int32_t _db_idx64_lowerbound(capi_name code, uint64_t scope, capi_name table, uint64_t* secondary, uint64_t* primary) {
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

static int32_t _db_idx64_upperbound(capi_name code, uint64_t scope, capi_name table, uint64_t* secondary, uint64_t* primary) {
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

static int32_t _db_idx64_end(capi_name code, uint64_t scope, capi_name table) {
    return GetApplyClient()->db_idx64_end(
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table)
    );
}

static int32_t _db_idx128_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const uint128_t* secondary) {
    return GetApplyClient()->db_idx128_store(
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(payer),
        to_raw_uint64(id),
        string((char *)secondary, 16)
    );    
}

static void _db_idx128_update(int32_t iterator, capi_name payer, const uint128_t* secondary) {
    GetApplyClient()->db_idx128_update(iterator, to_raw_uint64(payer), string((char *)secondary, 16));
}

static void _db_idx128_remove(int32_t iterator) {
    GetApplyClient()->db_idx128_remove(iterator);    
}

static int32_t _db_idx128_next(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx128_next(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

static int32_t _db_idx128_previous(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx128_previous(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

static int32_t _db_idx128_find_primary(capi_name code, uint64_t scope, capi_name table, uint128_t* secondary, uint64_t primary) {
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

static int32_t _db_idx128_find_secondary(capi_name code, uint64_t scope, capi_name table, const uint128_t* secondary, uint64_t* primary) {
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

static int32_t _db_idx128_lowerbound(capi_name code, uint64_t scope, capi_name table, uint128_t* secondary, uint64_t* primary) {
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

static int32_t _db_idx128_upperbound(capi_name code, uint64_t scope, capi_name table, uint128_t* secondary, uint64_t* primary) {
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

static int32_t _db_idx128_end(capi_name code, uint64_t scope, capi_name table) {
    return GetApplyClient()->db_idx128_end(
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table)
    );
}

static int32_t _db_idx256_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const uint128_t* data, uint32_t data_len ) {
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

static void _db_idx256_update(int32_t iterator, capi_name payer, const uint128_t* data, uint32_t data_len) {
    if (data_len != 2) {
        throw std::runtime_error("db_idx256_store: bad data length");
    }
    GetApplyClient()->db_idx256_update(iterator, to_raw_uint64(payer), string((char *)data, 32));    
}

static void _db_idx256_remove(int32_t iterator) {
    GetApplyClient()->db_idx256_remove(iterator);    
}

static int32_t _db_idx256_next(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx256_next(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

static int32_t _db_idx256_previous(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx256_previous(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

static int32_t _db_idx256_find_primary(capi_name code, uint64_t scope, capi_name table, uint128_t* data, uint32_t data_len, uint64_t primary) {
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

static int32_t _db_idx256_find_secondary(capi_name code, uint64_t scope, capi_name table, const uint128_t* data, uint32_t data_len, uint64_t* primary) {
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

static int32_t _db_idx256_lowerbound(capi_name code, uint64_t scope, capi_name table, uint128_t* data, uint32_t data_len, uint64_t* primary) {
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

static int32_t _db_idx256_upperbound(capi_name code, uint64_t scope, capi_name table, uint128_t* data, uint32_t data_len, uint64_t* primary) {
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

static int32_t _db_idx256_end(capi_name code, uint64_t scope, capi_name table) {
    return GetApplyClient()->db_idx256_end(
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table)
    );
}

static int32_t _db_idx_double_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const double* secondary) {
    return GetApplyClient()->db_idx_double_store(
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(payer),
        to_raw_uint64(id),
        string((char *)secondary, 8)
    );
}

static void _db_idx_double_update(int32_t iterator, capi_name payer, const double* secondary) {
    GetApplyClient()->db_idx_double_update(iterator, to_raw_uint64(payer), string((char *)secondary, 8));    
}

static void _db_idx_double_remove(int32_t iterator) {
    GetApplyClient()->db_idx_double_remove(iterator);    
}

static int32_t _db_idx_double_next(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx_double_next(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;    
}

static int32_t _db_idx_double_previous(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx_double_previous(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

static int32_t _db_idx_double_find_primary(capi_name code, uint64_t scope, capi_name table, double* secondary, uint64_t primary) {
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

static int32_t _db_idx_double_find_secondary(capi_name code, uint64_t scope, capi_name table, const double* secondary, uint64_t* primary) {
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

static int32_t _db_idx_double_lowerbound(capi_name code, uint64_t scope, capi_name table, double* secondary, uint64_t* primary) {
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

static int32_t _db_idx_double_upperbound(capi_name code, uint64_t scope, capi_name table, double* secondary, uint64_t* primary) {
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

static int32_t _db_idx_double_end(capi_name code, uint64_t scope, capi_name table) {
    return GetApplyClient()->db_idx_double_end(
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table)
    );
}

static int32_t _db_idx_long_double_store(uint64_t scope, capi_name table, capi_name payer, uint64_t id, const long double* secondary) {
    float128_t _secondary;
    extF80M_to_f128M((extFloat80_t *)secondary, &_secondary);
    return GetApplyClient()->db_idx_long_double_store(
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(payer),
        to_raw_uint64(id),
        string((char *)&_secondary, 16)
    );    
}

static void _db_idx_long_double_update(int32_t iterator, capi_name payer, const long double* secondary) {
    float128_t _secondary;
    extF80M_to_f128M((extFloat80_t *)secondary, &_secondary);
    GetApplyClient()->db_idx_long_double_update(iterator, to_raw_uint64(payer), string((char *)&_secondary, 16));    
}

static void _db_idx_long_double_remove(int32_t iterator) {
    GetApplyClient()->db_idx_long_double_remove(iterator);    
}

static int32_t _db_idx_long_double_next(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx_long_double_next(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;    
}

static int32_t _db_idx_long_double_previous(int32_t iterator, uint64_t* primary) {
    NextPreviousReturn ret;
    GetApplyClient()->db_idx_long_double_previous(ret, iterator);
    if (ret.iterator >= 0) {
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

static int32_t _db_idx_long_double_find_primary(capi_name code, uint64_t scope, capi_name table, long double* secondary, uint64_t primary) {
    FindPrimaryReturn ret;
    GetApplyClient()->db_idx_long_double_find_primary(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        to_raw_uint64(primary)

    );
    if (ret.iterator >= 0) {
        if (ret.secondary.size() != 16) {
            throw std::runtime_error("db_idx_long_double_find_primary: bad secondary return size");
        }
        float128_t _secondary;
        memcpy(&_secondary, ret.secondary.c_str(), ret.secondary.size());
        f128M_to_extF80M(&_secondary, (extFloat80_t *)secondary);
    }
    return ret.iterator;
}

static int32_t _db_idx_long_double_find_secondary(capi_name code, uint64_t scope, capi_name table, const long double* secondary, uint64_t* primary) {
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

static int32_t _db_idx_long_double_lowerbound(capi_name code, uint64_t scope, capi_name table, long double* secondary, uint64_t* primary) {
    LowerBoundUpperBoundReturn ret;
    float128_t _secondary;
    extF80M_to_f128M((extFloat80_t *)secondary, &_secondary);

    GetApplyClient()->db_idx_long_double_lowerbound(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        string((char *)&_secondary, 16),
        to_raw_uint64(*primary)
    );
    if (ret.iterator >= 0) {
        if (ret.secondary.size() != 16) {
            throw std::runtime_error("db_idx_long_double_lowerbound: bad secondary return size");
        }
        float128_t _secondary;
        memcpy(&_secondary, ret.secondary.c_str(), ret.secondary.size());
        f128M_to_extF80M(&_secondary, (extFloat80_t *)secondary);
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

static int32_t _db_idx_long_double_upperbound(capi_name code, uint64_t scope, capi_name table, long double* secondary, uint64_t* primary) {
    LowerBoundUpperBoundReturn ret;
    float128_t _secondary;
    extF80M_to_f128M((extFloat80_t *)secondary, &_secondary);
    GetApplyClient()->db_idx_long_double_upperbound(
        ret,
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table),
        string((char *)&_secondary, 16),
        to_raw_uint64(*primary)
    );
    if (ret.iterator >= 0) {
        if (ret.secondary.size() != 16) {
            throw std::runtime_error("db_idx_long_double_upperbound: bad secondary return size");
        }
        float128_t _secondary;
        memcpy(&_secondary, ret.secondary.c_str(), ret.secondary.size());
        f128M_to_extF80M(&_secondary, (extFloat80_t *)secondary);
        *primary = from_raw_uint64(ret.primary);
    }
    return ret.iterator;
}

static int32_t _db_idx_long_double_end(capi_name code, uint64_t scope, capi_name table) {
    return GetApplyClient()->db_idx_long_double_end(
        to_raw_uint64(code),
        to_raw_uint64(scope),
        to_raw_uint64(table)
    );
}

static int32_t _check_transaction_authorization( const char* trx_data,     uint32_t trx_size,
                                 const char* pubkeys_data, uint32_t pubkeys_size,
                                 const char* perms_data,   uint32_t perms_size) {
    string _trx_data = string(trx_data, trx_size);
    string _pubkeys_data = string(pubkeys_data, pubkeys_size);
    string _perms_data = string(_perms_data, perms_size);
    return GetApplyClient()->check_transaction_authorization(_trx_data, _pubkeys_data, _perms_data);
}

static int32_t _check_permission_authorization( capi_name account,
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

static int64_t _get_permission_last_used( capi_name account, capi_name permission ) {
    return GetApplyClient()->get_permission_last_used(to_raw_uint64(account), to_raw_uint64(permission));
}

static int64_t _get_account_creation_time( capi_name account ) {
    return GetApplyClient()->get_account_creation_time(to_raw_uint64(account));
}

static void _assert_sha256( const char* data, uint32_t length, const capi_checksum256* hash ) {
    GetApplyClient()->assert_sha256(string(data, length), string((char*)hash, 32));
}

static void _assert_sha1( const char* data, uint32_t length, const capi_checksum160* hash ) {
    GetApplyClient()->assert_sha1(string(data, length), string((char*)hash, 20));
}

static void _assert_sha512( const char* data, uint32_t length, const capi_checksum512* hash ) {
    GetApplyClient()->assert_sha512(string(data, length), string((char*)hash, 64));
}

static void _assert_ripemd160( const char* data, uint32_t length, const capi_checksum160* hash ) {
    GetApplyClient()->assert_ripemd160(string(data, length), string((char*)hash, 20));
}

static void _sha256( const char* data, uint32_t length, capi_checksum256* hash ) {
    string ret;
    GetApplyClient()->sha256(ret, string(data, length));
    memcpy(hash, ret.c_str(), 32);
}

static void _sha1( const char* data, uint32_t length, capi_checksum160* hash ) {
    string ret;
    GetApplyClient()->sha1(ret, string(data, length));
    memcpy(hash, ret.c_str(), 20);
}

static void _sha512( const char* data, uint32_t length, capi_checksum512* hash ) {
    string ret;
    GetApplyClient()->sha512(ret, string(data, length));
    memcpy(hash, ret.c_str(), 64);
}

static void _ripemd160( const char* data, uint32_t length, capi_checksum160* hash ) {
    string ret;
    GetApplyClient()->ripemd160(ret, string(data, length));
    memcpy(hash, ret.c_str(), 20);
}

static int _recover_key( const capi_checksum256* digest, const char* sig, size_t siglen, char* pub, size_t publen ) {
    string ret;
    GetApplyClient()->recover_key(ret, string((char*)digest, 32), string(sig, siglen));
    if (publen == 0) {
        return ret.size();
    }
    size_t copy_size = std::min(ret.size(), publen);
    memcpy(pub, ret.c_str(), copy_size);
    return copy_size;
}

static void _assert_recover_key( const capi_checksum256* digest, const char* sig, size_t siglen, const char* pub, size_t publen ) {
    GetApplyClient()->assert_recover_key(string((char*)digest, 32), string(sig, siglen), string(pub, publen));
}

static uint32_t _read_action_data( void* msg, uint32_t len ) {
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

static uint32_t _action_data_size() {
    return GetApplyClient()->action_data_size();
}

static void _require_recipient( capi_name name ) {
    GetApplyClient()->require_recipient(to_raw_uint64(name));
}

static void _require_auth( capi_name name ) {
    GetApplyClient()->require_auth(to_raw_uint64(name));
}

static bool _has_auth( capi_name name ) {
    return GetApplyClient()->has_auth(to_raw_uint64(name));
}

static void _require_auth2( capi_name name, capi_name permission ) {
    GetApplyClient()->require_auth2(to_raw_uint64(name), to_raw_uint64(permission));
}

static bool _is_account( capi_name name ) {
    return GetApplyClient()->is_account(to_raw_uint64(name));
}

static void _send_inline(char *serialized_action, size_t size) {
    GetApplyClient()->send_inline(string(serialized_action, size));
}

static void _send_context_free_inline(char *serialized_action, size_t size) {
    GetApplyClient()->send_context_free_inline(string(serialized_action, size));
}

static uint64_t  _publication_time() {
    Uint64 ret;
    GetApplyClient()->publication_time(ret);
    return  from_raw_uint64(ret);
}

static capi_name _current_receiver() {
    Uint64 ret;
    GetApplyClient()->current_receiver(ret);
    return from_raw_uint64(ret);
}

static void _prints( const char* cstr ) {
    GetApplyClient()->prints(string(cstr, strlen(cstr)));
}

static void _prints_l( const char* cstr, uint32_t len) {
    GetApplyClient()->prints(string(cstr, len));
}

static void _printi( int64_t value ) {
    GetApplyClient()->printi(value);
}

static void _printui( uint64_t value ) {
    Uint64 _value;
    _value.rawValue = string((char *)&value, 8);
    GetApplyClient()->printui(_value);
}

static void _printi128( const int128_t* value ) {
    string _value((char *)value, 16);
    GetApplyClient()->printi128(_value);
}

static void _printui128( const uint128_t* value ) {
    string _value((char *)value, 16);
    GetApplyClient()->printui128(_value);
}

static void _printsf(float value) {
    string _value((char *)&value, 4);
    GetApplyClient()->printsf(_value);
}

static void _printdf(double value) {
    string _value((char *)&value, 8);
    GetApplyClient()->printdf(_value);
}

static void _printqf(const long double* value) {
    float128_t f;
    extF80M_to_f128M((extFloat80_t *)value, &f);
    string _value((char *)&f, 16);
    GetApplyClient()->printqf(_value);
}

static void _printn( uint64_t name ) {
    Uint64 _name;
    _name.rawValue = string((char *)&name, 8);
    GetApplyClient()->printn(_name);
}

static void _printhex( const void* data, uint32_t datalen ) {
    GetApplyClient()->printhex(string((char *)data, datalen));
}

static void _eosio_assert( uint32_t test, const char* msg ) {
    if (test) {
        return;
    }
    GetApplyClient()->eosio_assert(0, string(msg));
}

static void _eosio_assert_message( uint32_t test, const char* msg, uint32_t msg_len ) {
    if (test) {
        return;
    }
    GetApplyClient()->eosio_assert_message(0, string(msg, msg_len));
}

static void _eosio_assert_code( uint32_t test, uint64_t code ) {
    if (test) {
        return;
    }
    GetApplyClient()->eosio_assert_code(0, to_raw_uint64(code));
}

static uint64_t _current_time() {
    Uint64 value;
    GetApplyClient()->current_time(value);
    return from_raw_uint64(value);
}

static bool _is_feature_activated( const capi_checksum256* feature_digest ) {
    return GetApplyClient()->is_feature_activated(string((char *)feature_digest, 32));
}

static capi_name _get_sender() {
    Uint64 value;
    GetApplyClient()->get_sender(value);
    return from_raw_uint64(value);
}

static void _get_resource_limits( capi_name account, int64_t* ram_bytes, int64_t* net_weight, int64_t* cpu_weight ) {
    GetResourceLimitsReturn ret;
    Uint64 _account = to_raw_uint64(account);
    GetApplyClient()->get_resource_limits(ret, _account);
    *ram_bytes = ret.ram_bytes;
    *net_weight = ret.net_weight;
    *cpu_weight = ret.cpu_weight;
}

static void _set_resource_limits( capi_name account, int64_t ram_bytes, int64_t net_weight, int64_t cpu_weight ) {
    GetApplyClient()->set_resource_limits(to_raw_uint64(account), ram_bytes, net_weight, cpu_weight);
}

static int64_t _set_proposed_producers( char *producer_data, uint32_t producer_data_size ) {
    return GetApplyClient()->set_proposed_producers(string(producer_data, producer_data_size));
}

static int64_t _set_proposed_producers_ex( uint64_t producer_data_format, char *producer_data, uint32_t producer_data_size ) {
    return GetApplyClient()->set_proposed_producers_ex(to_raw_uint64(producer_data_format), string(producer_data, producer_data_size));
}

static bool _is_privileged( capi_name account ) {
    return GetApplyClient()->is_privileged(to_raw_uint64(account));
}

static void _set_privileged( capi_name account, bool is_priv ) {
    GetApplyClient()->set_privileged(to_raw_uint64(account), is_priv);
}

static void _set_blockchain_parameters_packed( char* data, uint32_t datalen ) {
    GetApplyClient()->set_blockchain_parameters_packed(string(data, datalen));
}

static uint32_t _get_blockchain_parameters_packed( char* data, uint32_t datalen ) {
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

static void _preactivate_feature( const capi_checksum256* feature_digest ) {
    GetApplyClient()->preactivate_feature(string((char *)feature_digest, 32));
}

static void _send_deferred(const uint128_t& sender_id, capi_name payer, const char *serialized_transaction, size_t size, uint32_t replace_existing) {
    GetApplyClient()->send_deferred(string((char *)&sender_id, 16), to_raw_uint64(payer), string(serialized_transaction, size), replace_existing);
}

static int _cancel_deferred(const uint128_t& sender_id) {
    return GetApplyClient()->cancel_deferred(string((char*)&sender_id, 16));
}

static size_t _read_transaction(char *buffer, size_t size) {
    string ret;
    GetApplyClient()->read_transaction(ret);
    if (size == 0) {
        return ret.size();
    }
    size_t copy_size = std::min(ret.size(), size);
    memcpy(buffer, ret.c_str(), ret.size());
    return copy_size;
}

static size_t _transaction_size() {
    return GetApplyClient()->transaction_size();
}

static int _tapos_block_num() {
    return GetApplyClient()->tapos_block_num();
}

static int _tapos_block_prefix() {
    return GetApplyClient()->tapos_block_prefix();
}

static uint32_t _expiration() {
    return GetApplyClient()->expiration();
}

static int _get_action( uint32_t type, uint32_t index, char* buff, size_t size ) {
    string ret;
    GetApplyClient()->get_action(ret, type, index);
    if (size == 0) {
        return ret.size();
    }
    size_t copy_size = std::min(ret.size(), size);
    memcpy(buff, ret.c_str(), ret.size());
    return copy_size;
}

static int _get_context_free_data( uint32_t index, char* buff, size_t size ) {
    string ret;
    GetApplyClient()->get_context_free_data(ret, index);
    if (size == 0) {
        return ret.size();
    }
    size_t copy_size = std::min(ret.size(), size);
    memcpy(buff, ret.c_str(), ret.size());
    return copy_size;
}

static void _set_action_return_value(const char *data, uint32_t data_size) {
    GetApplyClient()->set_action_return_value(string(data, data_size));
}

static uint32_t _get_code_hash(uint64_t account, uint32_t struct_version, char* packed_result, uint32_t packed_result_len) {
    string ret;
    GetApplyClient()->get_code_hash(ret, to_raw_uint64(account), struct_version);
    size_t copy_size = std::min(ret.size(), (size_t)packed_result_len);
    memcpy(packed_result, ret.c_str(), copy_size);
    return copy_size;
}

static uint32_t _get_block_num() {
    return (uint32_t)GetApplyClient()->get_block_num();
}

static void _sha3( const char* data, uint32_t data_len, char* hash, uint32_t hash_len, int32_t keccak ) {
    string ret;
    GetApplyClient()->sha3(ret, string(data, data_len), keccak);
    size_t copy_size = std::min(ret.size(), (size_t)hash_len);
    memcpy(hash, ret.c_str(), copy_size);
}

static int32_t _blake2_f( uint32_t rounds, const char* state, uint32_t state_len, const char* msg, uint32_t msg_len, 
                const char* t0_offset, uint32_t t0_len, const char* t1_offset, uint32_t t1_len, int32_t final, char* result, uint32_t result_len) {
    string ret;
    GetApplyClient()->blake2_f(ret, rounds, string(state, state_len), string(msg, msg_len), string(t0_offset, t0_len), string(t1_offset, t1_len), final);
    if (ret.size() == 0) {
        return -1;
    }
    size_t copy_size = std::min(ret.size(), (size_t)result_len);
    memcpy(result, ret.c_str(), copy_size);
    return 0;
}

static int32_t _k1_recover( const char* sig, uint32_t sig_len, const char* dig, uint32_t dig_len, char* pub, uint32_t pub_len) {
    string ret;
    GetApplyClient()->k1_recover(ret, string(sig, sig_len), string(dig, dig_len));
    if (ret.size() == 0) {
        return -1;
    }
    size_t copy_size = std::min(ret.size(), (size_t)pub_len);
    memcpy(pub, ret.c_str(), copy_size);
    return 0;
}

static int32_t _alt_bn128_add( const char* op1, uint32_t op1_len, const char* op2, uint32_t op2_len, char* result, uint32_t result_len) {
    string ret;
    GetApplyClient()->alt_bn128_add(ret, string(op1, op1_len), string(op2, op2_len));
    if (ret.size() == 0) {
        return -1;
    }
    size_t copy_size = std::min(ret.size(), (size_t)result_len);
    memcpy(result, ret.c_str(), copy_size);
    return 0;
}

static int32_t _alt_bn128_mul( const char* g1, uint32_t g1_len, const char* scalar, uint32_t scalar_len, char* result, uint32_t result_len) {
    string ret;
    GetApplyClient()->alt_bn128_mul(ret, string(g1, g1_len), string(scalar, scalar_len));
    if (ret.size() == 0) {
        return -1;
    }
    size_t copy_size = std::min(ret.size(), (size_t)result_len);
    memcpy(result, ret.c_str(), copy_size);
    return 0;
}

static int32_t _alt_bn128_pair( const char* pairs, uint32_t pairs_len) {
    return GetApplyClient()->alt_bn128_pair(string(pairs, pairs_len));
}

static int32_t _mod_exp( const char* base, uint32_t base_len, const char* exp, uint32_t exp_len, const char* mod, uint32_t mod_len, char* result, uint32_t result_len) {
    string ret;
    GetApplyClient()->mod_exp(ret, string(base, base_len), string(exp, exp_len), string(mod, mod_len));
    if (ret.size() == 0) {
        return -1;
    }
    size_t copy_size = std::min(ret.size(), (size_t)result_len);
    memcpy(result, ret.c_str(), copy_size);
    return 0;    
}

static bool initialized = false;
static struct IntrinsicsFuncs g_intrinsics_func;

void init_intrinsics_func() {
    if (initialized) {
        return;
    }
    initialized = true;

    g_intrinsics_func.get_active_producers = _get_active_producers;
    g_intrinsics_func.db_store_i64 = _db_store_i64;
    g_intrinsics_func.db_update_i64 = _db_update_i64;
    g_intrinsics_func.db_remove_i64 = _db_remove_i64;
    g_intrinsics_func.db_get_i64 = _db_get_i64;
    g_intrinsics_func.db_next_i64 = _db_next_i64;
    g_intrinsics_func.db_previous_i64 = _db_previous_i64;
    g_intrinsics_func.db_find_i64 = _db_find_i64;
    g_intrinsics_func.db_lowerbound_i64 = _db_lowerbound_i64;
    g_intrinsics_func.db_upperbound_i64 = _db_upperbound_i64;
    g_intrinsics_func.db_end_i64 = _db_end_i64;
    g_intrinsics_func.db_idx64_store = _db_idx64_store;
    g_intrinsics_func.db_idx64_update = _db_idx64_update;
    g_intrinsics_func.db_idx64_remove = _db_idx64_remove;
    g_intrinsics_func.db_idx64_next = _db_idx64_next;
    g_intrinsics_func.db_idx64_previous = _db_idx64_previous;
    g_intrinsics_func.db_idx64_find_primary = _db_idx64_find_primary;
    g_intrinsics_func.db_idx64_find_secondary = _db_idx64_find_secondary;
    g_intrinsics_func.db_idx64_lowerbound = _db_idx64_lowerbound;
    g_intrinsics_func.db_idx64_upperbound = _db_idx64_upperbound;
    g_intrinsics_func.db_idx64_end = _db_idx64_end;
    g_intrinsics_func.db_idx128_store = _db_idx128_store;
    g_intrinsics_func.db_idx128_update = _db_idx128_update;
    g_intrinsics_func.db_idx128_remove = _db_idx128_remove;
    g_intrinsics_func.db_idx128_next = _db_idx128_next;
    g_intrinsics_func.db_idx128_previous = _db_idx128_previous;
    g_intrinsics_func.db_idx128_find_primary = _db_idx128_find_primary;
    g_intrinsics_func.db_idx128_find_secondary = _db_idx128_find_secondary;
    g_intrinsics_func.db_idx128_lowerbound = _db_idx128_lowerbound;
    g_intrinsics_func.db_idx128_upperbound = _db_idx128_upperbound;
    g_intrinsics_func.db_idx128_end = _db_idx128_end;
    g_intrinsics_func.db_idx256_store = _db_idx256_store;
    g_intrinsics_func.db_idx256_update = _db_idx256_update;
    g_intrinsics_func.db_idx256_remove = _db_idx256_remove;
    g_intrinsics_func.db_idx256_next = _db_idx256_next;
    g_intrinsics_func.db_idx256_previous = _db_idx256_previous;
    g_intrinsics_func.db_idx256_find_primary = _db_idx256_find_primary;
    g_intrinsics_func.db_idx256_find_secondary = _db_idx256_find_secondary;
    g_intrinsics_func.db_idx256_lowerbound = _db_idx256_lowerbound;
    g_intrinsics_func.db_idx256_upperbound = _db_idx256_upperbound;
    g_intrinsics_func.db_idx256_end = _db_idx256_end;
    g_intrinsics_func.db_idx_double_store = _db_idx_double_store;
    g_intrinsics_func.db_idx_double_update = _db_idx_double_update;
    g_intrinsics_func.db_idx_double_remove = _db_idx_double_remove;
    g_intrinsics_func.db_idx_double_next = _db_idx_double_next;
    g_intrinsics_func.db_idx_double_previous = _db_idx_double_previous;
    g_intrinsics_func.db_idx_double_find_primary = _db_idx_double_find_primary;
    g_intrinsics_func.db_idx_double_find_secondary = _db_idx_double_find_secondary;
    g_intrinsics_func.db_idx_double_lowerbound = _db_idx_double_lowerbound;
    g_intrinsics_func.db_idx_double_upperbound = _db_idx_double_upperbound;
    g_intrinsics_func.db_idx_double_end = _db_idx_double_end;
    g_intrinsics_func.db_idx_long_double_store = _db_idx_long_double_store;
    g_intrinsics_func.db_idx_long_double_update = _db_idx_long_double_update;
    g_intrinsics_func.db_idx_long_double_remove = _db_idx_long_double_remove;
    g_intrinsics_func.db_idx_long_double_next = _db_idx_long_double_next;
    g_intrinsics_func.db_idx_long_double_previous = _db_idx_long_double_previous;
    g_intrinsics_func.db_idx_long_double_find_primary = _db_idx_long_double_find_primary;
    g_intrinsics_func.db_idx_long_double_find_secondary = _db_idx_long_double_find_secondary;
    g_intrinsics_func.db_idx_long_double_lowerbound = _db_idx_long_double_lowerbound;
    g_intrinsics_func.db_idx_long_double_upperbound = _db_idx_long_double_upperbound;
    g_intrinsics_func.db_idx_long_double_end = _db_idx_long_double_end;
    g_intrinsics_func.check_transaction_authorization = _check_transaction_authorization;
    g_intrinsics_func.check_permission_authorization = _check_permission_authorization;
    g_intrinsics_func.get_permission_last_used = _get_permission_last_used;
    g_intrinsics_func.get_account_creation_time = _get_account_creation_time;
    g_intrinsics_func.assert_sha256 = _assert_sha256;
    g_intrinsics_func.assert_sha1 = _assert_sha1;
    g_intrinsics_func.assert_sha512 = _assert_sha512;
    g_intrinsics_func.assert_ripemd160 = _assert_ripemd160;
    g_intrinsics_func.sha256 = _sha256;
    g_intrinsics_func.sha1 = _sha1;
    g_intrinsics_func.sha512 = _sha512;
    g_intrinsics_func.ripemd160 = _ripemd160;
    g_intrinsics_func.recover_key = _recover_key;
    g_intrinsics_func.assert_recover_key = _assert_recover_key;
    g_intrinsics_func.read_action_data = _read_action_data;
    g_intrinsics_func.action_data_size = _action_data_size;
    g_intrinsics_func.require_recipient = _require_recipient;
    g_intrinsics_func.require_auth = _require_auth;
    g_intrinsics_func.has_auth = _has_auth;
    g_intrinsics_func.require_auth2 = _require_auth2;
    g_intrinsics_func.is_account = _is_account;
    g_intrinsics_func.send_inline = _send_inline;
    g_intrinsics_func.send_context_free_inline = _send_context_free_inline;
    g_intrinsics_func.publication_time = _publication_time;
    g_intrinsics_func.current_receiver = _current_receiver;
    g_intrinsics_func.prints = _prints;
    g_intrinsics_func.prints_l = _prints_l;
    g_intrinsics_func.printi = _printi;
    g_intrinsics_func.printui = _printui;
    g_intrinsics_func.printi128 = _printi128;
    g_intrinsics_func.printui128 = _printui128;
    g_intrinsics_func.printsf = _printsf;
    g_intrinsics_func.printdf = _printdf;
    g_intrinsics_func.printqf = _printqf;
    g_intrinsics_func.printn = _printn;
    g_intrinsics_func.printhex = _printhex;
    g_intrinsics_func.eosio_assert = _eosio_assert;
    g_intrinsics_func.eosio_assert_message = _eosio_assert_message;
    g_intrinsics_func.eosio_assert_code = _eosio_assert_code;
    g_intrinsics_func.current_time = _current_time;
    g_intrinsics_func.is_feature_activated = _is_feature_activated;
    g_intrinsics_func.get_sender = _get_sender;
    g_intrinsics_func.get_resource_limits = _get_resource_limits;
    g_intrinsics_func.set_resource_limits = _set_resource_limits;
    g_intrinsics_func.set_proposed_producers = _set_proposed_producers;
    g_intrinsics_func.set_proposed_producers_ex = _set_proposed_producers_ex;
    g_intrinsics_func.is_privileged = _is_privileged;
    g_intrinsics_func.set_privileged = _set_privileged;
    g_intrinsics_func.set_blockchain_parameters_packed = _set_blockchain_parameters_packed;
    g_intrinsics_func.get_blockchain_parameters_packed = _get_blockchain_parameters_packed;
    g_intrinsics_func.preactivate_feature = _preactivate_feature;
    g_intrinsics_func.send_deferred = _send_deferred;
    g_intrinsics_func.cancel_deferred = _cancel_deferred;
    g_intrinsics_func.read_transaction = _read_transaction;
    g_intrinsics_func.transaction_size = _transaction_size;
    g_intrinsics_func.tapos_block_num = _tapos_block_num;
    g_intrinsics_func.tapos_block_prefix = _tapos_block_prefix;
    g_intrinsics_func.expiration = _expiration;
    g_intrinsics_func.get_action = _get_action;
    g_intrinsics_func.get_context_free_data = _get_context_free_data;
    g_intrinsics_func.set_action_return_value = _set_action_return_value;

    g_intrinsics_func.set_action_return_value = _set_action_return_value;
    g_intrinsics_func.get_code_hash = _get_code_hash;
    g_intrinsics_func.get_block_num = _get_block_num;

    g_intrinsics_func.sha3 = _sha3;
    g_intrinsics_func.blake2_f = _blake2_f;
    g_intrinsics_func.k1_recover = _k1_recover;
    g_intrinsics_func.alt_bn128_add = _alt_bn128_add;
    g_intrinsics_func.alt_bn128_mul = _alt_bn128_mul;
    g_intrinsics_func.alt_bn128_pair = _alt_bn128_pair;
    g_intrinsics_func.mod_exp = _mod_exp;
    intrinsics_init(&g_intrinsics_func);
}

class InitIntrinsics {
public:
    InitIntrinsics() {
        init_intrinsics_func();
    }
};

InitIntrinsics _init;
