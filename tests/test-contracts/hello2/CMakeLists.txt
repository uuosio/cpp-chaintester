add_library( hello_static SHARED
    hello.cpp
    main.cpp
)

set_target_properties(hello_static PROPERTIES CXX_VISIBILITY_PRESET hidden)


target_compile_options(hello_static PRIVATE 
    -g
    -O0
    ${COVERAGE_OPTIONS}
    -DEOSIO_NATIVE
    -Wno-unknown-attributes
)

target_include_directories(hello_static PUBLIC 
    ${CMAKE_SOURCE_DIR}/libs/boost/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CDT_PATH}/include/libcxx 
    ${CDT_PATH}/include/libc 
    ${CDT_PATH}/include/eosiolib/capi 
    ${CDT_PATH}/include/eosiolib/native 
    ${CDT_PATH}/include/eosiolib/core 
    ${CDT_PATH}/include/eosiolib/contracts 
)

target_link_options(hello_static PRIVATE ${COVERAGE_OPTIONS})

target_link_libraries (hello_static
    chain_static
)
