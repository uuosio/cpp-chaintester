#pragma once

#include <exception>
#include "jsonobject.h"

class chain_exception: public std::exception {
private:
    JsonObject o;
private:
    chain_exception& operator = (const chain_exception& ex) noexcept;
public:
    chain_exception(const string& s) noexcept : std::exception(), o(s) {
    }

    chain_exception (const chain_exception& ex) noexcept: o(ex.value().to_string()) {
    }

    const JsonObject& value() const {
        return o;
    }

    ~chain_exception() {

    }

    const char* what() const noexcept {
        return o.to_string().c_str();
    }
};
