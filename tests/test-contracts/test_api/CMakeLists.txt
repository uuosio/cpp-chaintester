cmake_minimum_required(VERSION 3.21)

project(testapi)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( testapi testapi test_api.cpp)
target_include_directories( testapi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include )
configure_file(testapi.abi ${CMAKE_CURRENT_BINARY_DIR}/testapi.abi COPYONLY )
