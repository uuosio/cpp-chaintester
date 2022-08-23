import os
import shutil

def find_eosio_cdt_path():
    eosio_cpp = shutil.which('eosio-cpp')
    if not eosio_cpp:
        raise Exception("eosio.cdt not installed, please refer to https://github.com/eosio/eosio.cdt for an installation guide")
    eosio_cpp = os.path.realpath(eosio_cpp)
    eosio_cpp = os.path.dirname(eosio_cpp)
    return os.path.dirname(eosio_cpp)

print(find_eosio_cdt_path(), end='')
