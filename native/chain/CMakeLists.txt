add_library( chain_static
    src/crypto.cpp
    src/eosiolib.cpp
    src/intrinsics.cpp
)

set_target_properties(chain_static PROPERTIES CXX_VISIBILITY_PRESET hidden)


target_compile_options(chain_static PRIVATE 
    -g
    -O0
    -fprofile-instr-generate -fcoverage-mapping
    -DEOSIO_NATIVE
    -Wno-unknown-attributes
)

target_include_directories(chain_static PUBLIC 
    ${CMAKE_SOURCE_DIR}/libs/boost/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CDT_PATH}/include/libcxx 
    ${CDT_PATH}/include/libc 
    ${CDT_PATH}/include/eosiolib/capi 
    ${CDT_PATH}/include/eosiolib/native 
    ${CDT_PATH}/include/eosiolib/core 
    ${CDT_PATH}/include/eosiolib/contracts 
)

target_link_options(chain_static PRIVATE -fprofile-instr-generate -fcoverage-mapping)
