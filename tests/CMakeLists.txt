add_subdirectory(test-contracts)

add_executable( tests 
    src/main.cpp
    src/test.cpp
    src/test_hello.cpp
    src/test_api_db.cpp
    src/test_multi_index.cpp
    src/intrinsics_test.cpp
    src/test_api.cpp
    src/test_new_intrinsics.cpp
    src/test_jsonobject.cpp
)

target_compile_options(tests PRIVATE 
    -g
    -O0
    -DEOSIO_NATIVE
    -Wno-attributes
    -Wno-deprecated-declarations
    -Wno-unused-value
)

target_link_options(tests PRIVATE ${COVERAGE_OPTIONS})

target_link_libraries ( tests
    hello_native
    test_api_native
    test_api_db_native
    test_api_multi_index_native
    new_intrinsics_native
    intrinsics_native
    chaintester
)

add_dependencies(tests chaintester)

target_include_directories(tests PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_BINARY_DIR}"
    ${CMAKE_CURRENT_SOURCE_DIR}/../native/intrinsics/include
    "${CMAKE_BINARY_DIR}/generated-includes"
)

configure_file(src/generated.h.in ${CMAKE_CURRENT_BINARY_DIR}/generated.h @ONLY )
