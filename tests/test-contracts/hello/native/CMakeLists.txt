add_library( hello_native
    ../src/hello.cpp
    ../src/main.cpp
)

set_target_properties(hello_native PROPERTIES CXX_VISIBILITY_PRESET hidden)

target_compile_options(hello_native PRIVATE 
    -g
    -O0
    -fprofile-instr-generate -fcoverage-mapping
    -DEOSIO_NATIVE
    -Wno-unknown-attributes
)

target_include_directories(hello_native PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_SOURCE_DIR}/libs/cdt/include
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/capi
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/native
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/core
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/contracts
)

target_link_options(hello_native PRIVATE -fprofile-instr-generate -fcoverage-mapping)

target_link_libraries (hello_native
    chain_static
)
