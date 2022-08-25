add_subdirectory(hello)
add_subdirectory(test-contracts)
add_subdirectory(chainlib)
add_subdirectory(intrinsics)

add_dependencies(hello_native_project intrinsics-native-project libc_native_project libcxx_native_project)
add_dependencies(test-api-native-project intrinsics-native-project libc_native_project libcxx_native_project)
add_dependencies(test-api-multi-index-native-project intrinsics-native-project libc_native_project libcxx_native_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable( tests 
    src/test.cpp
    src/test_hello.cpp
    src/intrinsics_test.cpp
    src/test_api.cpp
    src/utils.cpp
)

target_link_libraries ( tests
    chaintester
    Catch2
    Catch2WithMain
    # ${CMAKE_CURRENT_BINARY_DIR}/hello/native/libhello_static.so
    # ${CMAKE_CURRENT_BINARY_DIR}/test-contracts/test_api_native/libtest_api_static.a
    # ${CMAKE_CURRENT_BINARY_DIR}/test-contracts/test_api_multi_index/native/libtest_api_multi_index_static.a
    # ${CMAKE_CURRENT_BINARY_DIR}/chainlib/native/libchain_static.a
    ${CMAKE_BINARY_DIR}/libs/thrift/lib/libthriftd${CMAKE_STATIC_LIBRARY_SUFFIX}
    ${CMAKE_DL_LIBS}
)

add_dependencies(tests chaintester Catch2 Catch2WithMain
    thrift_external
    chainlib-project
    hello_project
    hello_native_project
    test-api-project
    test-api-native-project
    test-api-multi-index-project
    test-api-multi-index-native-project
)

target_include_directories(tests PUBLIC
    "${CMAKE_SOURCE_DIR}/libs/thrift/lib/cpp/src"
    "${CMAKE_SOURCE_DIR}/libs/Catch2/src"
    "${CMAKE_SOURCE_DIR}/chaintester/src"
    "${CMAKE_BINARY_DIR}/generated-includes"
    "${CMAKE_CURRENT_BINARY_DIR}"
)

configure_file(src/test.h.in ${CMAKE_CURRENT_BINARY_DIR}/test.h @ONLY )
