#pragma once

#include <exception>
#include <memory>
#include "jsonobject.hpp"

class ChainException: public std::exception {
private:
    std::shared_ptr<JsonObject> o;
private:
    ChainException& operator = (const ChainException& ex) noexcept;
public:
    ChainException(const string& s) noexcept : std::exception() {
        o = std::make_shared<JsonObject>(s);
    }

    ChainException (const ChainException& ex) noexcept {
        o = std::make_shared<JsonObject>(ex.what());
    }

    const JsonObject& value() const {
        return *o;
    }

    void require_exception(const string& exception_type, const string& exception_message) {
        if (!o->HasMember("except")) {
            throw *this;
        }
        auto& except = (*o)["except"];
        if (except["name"].GetString() == exception_type) {
            if ("wasm_execution_error" == exception_type) {
                auto s =  except["stack"][0]["format"].GetString();
                if (string(s).find(exception_message) != std::string::npos) {
                    return;
                }
            } else if ("eosio_assert_message_exception" == exception_type) {
                auto s =  except["stack"][0]["data"]["s"].GetString();
                if(string(s).find(exception_message) != std::string::npos) {
                    return;
                }
            } else {
                auto s =  except["stack"][0]["format"].GetString();
                if (string(s).find(exception_message) != std::string::npos) {
                    return;
                }
            }
        }
        throw *this;
    }

    void require_assertion(const string& exception_message) {
        require_exception("eosio_assert_message_exception", exception_message);
    }

    ~ChainException() {

    }

    const char* what() const noexcept {
        return o->to_string().c_str();
    }
};
