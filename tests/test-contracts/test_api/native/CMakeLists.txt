add_library( test_api_native ${CMAKE_CURRENT_SOURCE_DIR}/../test_api.cpp)

target_compile_options(test_api_native PRIVATE
    -g
    -O0
    -fprofile-arcs -ftest-coverage
    -DEOSIO_NATIVE
    -Wno-unknown-attributes
)

target_link_options(test_api_native PRIVATE -fprofile-arcs -ftest-coverage)

target_include_directories(test_api_native PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CDT_INCLUDE_PATH}
)

target_link_libraries (test_api_native
    ${CMAKE_BINARY_DIR}/native/chain/libchain_static.a
)
