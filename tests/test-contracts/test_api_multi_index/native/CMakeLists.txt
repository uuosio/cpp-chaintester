add_library( test_api_multi_index_native
    main.cpp
    ../test_api_multi_index.cpp
)

set_target_properties(test_api_multi_index_native PROPERTIES CXX_VISIBILITY_PRESET hidden)

target_compile_options(test_api_multi_index_native PRIVATE 
    -g
    -O0
    -fprofile-arcs -ftest-coverage
    -DEOSIO_NATIVE
    -Wno-unknown-attributes
    -Wno-deprecated-declarations
)

target_include_directories(test_api_multi_index_native PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_SOURCE_DIR}/libs/cdt/include
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/capi
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/native
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/core
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/contracts
)

target_link_options(test_api_multi_index_native PRIVATE -fprofile-arcs -ftest-coverage)

target_link_libraries (test_api_multi_index_native
    chain_static
)
