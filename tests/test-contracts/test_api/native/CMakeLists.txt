add_library( test_api_native SHARED ${CMAKE_CURRENT_SOURCE_DIR}/../test_api.cpp)

target_compile_options(test_api_native PRIVATE
    -g
    -O0
    # -fprofile-instr-generate -fcoverage-mapping
    -DEOSIO_NATIVE
    -Wno-unknown-attributes
)

# target_link_options(test_api_native PRIVATE -fprofile-instr-generate -fcoverage-mapping)

target_include_directories(test_api_native PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CDT_PATH}/include/libcxx 
    ${CDT_PATH}/include/libc 
    ${CDT_PATH}/include 
    ${CDT_PATH}/include/eosiolib/capi 
    ${CDT_PATH}/include/eosiolib/native 
    ${CDT_PATH}/include/eosiolib/core 
    ${CDT_PATH}/include/eosiolib/contracts 
)

target_link_libraries (test_api_native
    ${CMAKE_BINARY_DIR}/native/chain/libchain_static.a
)
