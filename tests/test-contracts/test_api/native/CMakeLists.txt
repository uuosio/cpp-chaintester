add_library( test_api_native ${CMAKE_CURRENT_SOURCE_DIR}/../test_api.cpp)

target_compile_options(test_api_native PRIVATE
    -g
    -O0
    # -fprofile-instr-generate -fcoverage-mapping
    -DEOSIO_NATIVE
    -Wno-unknown-attributes
)

# target_link_options(test_api_native PRIVATE -fprofile-instr-generate -fcoverage-mapping)

target_include_directories(test_api_native PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_SOURCE_DIR}/libs/cdt/include
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/capi
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/native
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/core
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/contracts
)

target_link_libraries (test_api_native
    ${CMAKE_BINARY_DIR}/native/chain/libchain_static.a
)
