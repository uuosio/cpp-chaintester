add_library( chain_static
    src/crypto.cpp
    src/eosiolib.cpp
    src/intrinsics.cpp
)

set_target_properties(chain_static PROPERTIES CXX_VISIBILITY_PRESET hidden)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(PLATFORM_OPTIONS "-fPIC")
endif()

target_compile_options(chain_static PRIVATE 
    -g
    -O0
    # -fprofile-instr-generate -fcoverage-mapping
    -DEOSIO_NATIVE
    -Wno-unknown-attributes
    ${PLATFORM_OPTIONS}
)

target_include_directories(chain_static PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/libs/cdt/include
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/capi
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/native
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/core
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/contracts

)

# target_link_options(chain_static PRIVATE -fprofile-instr-generate -fcoverage-mapping)
