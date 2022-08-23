add_subdirectory(hello)

add_executable( tests 
    src/test.cpp
    src/test_hello.cpp
    src/intrinsics_test.cpp
)

target_link_libraries ( tests
    chaintester
    Catch2
    Catch2WithMain
    ${CMAKE_CURRENT_BINARY_DIR}/hello/hello/libhello_static.a
)

add_dependencies(tests chaintester Catch2 Catch2WithMain hello_project)

target_include_directories(tests PUBLIC
    "${CMAKE_SOURCE_DIR}/libs/thrift/lib/cpp/src"
    "${CMAKE_SOURCE_DIR}/libs/Catch2/src"
    "${CMAKE_SOURCE_DIR}/chaintester/src"
    "${CMAKE_BINARY_DIR}/generated-includes"
    "${CMAKE_CURRENT_BINARY_DIR}"
)

configure_file(src/test.h.in ${CMAKE_CURRENT_BINARY_DIR}/test.h @ONLY )
