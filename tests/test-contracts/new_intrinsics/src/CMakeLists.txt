cmake_minimum_required(VERSION 3.16.3)

project(hello)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(cdt)

add_contract( new_intrinsics new_intrinsics new_intrinsics.cpp main.cpp)
target_include_directories( new_intrinsics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include )
# target_ricardian_directory( hello ${CMAKE_CURRENT_SOURCE_DIR}/../ricardian )
