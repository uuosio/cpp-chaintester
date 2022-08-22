add_executable( tests 
    src/test.cpp
)

target_link_libraries ( tests chaintester Catch2 Catch2WithMain)

add_dependencies(tests chaintester Catch2 Catch2WithMain)

target_include_directories(tests PUBLIC
    "${CMAKE_SOURCE_DIR}/libs/thrift/lib/cpp/src"
    "${CMAKE_SOURCE_DIR}/libs/Catch2/src"
    "${CMAKE_SOURCE_DIR}/chaintester/src"
    "${CMAKE_BINARY_DIR}/generated-includes"
    "${CMAKE_CURRENT_BINARY_DIR}"
)

configure_file(src/test.h.in ${CMAKE_CURRENT_BINARY_DIR}/test.h @ONLY )
configure_file(hello.wasm ${CMAKE_CURRENT_BINARY_DIR}/hello.wasm COPYONLY)
configure_file(hello.abi ${CMAKE_CURRENT_BINARY_DIR}/hello.abi COPYONLY)
