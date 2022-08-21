add_executable ( tests 
    src/test.cpp
)

target_link_libraries ( tests chaintester )

add_dependencies(tests chaintester)


target_include_directories(tests PUBLIC
    "${CMAKE_SOURCE_DIR}/libs/thrift/lib/cpp/src"
    "${CMAKE_SOURCE_DIR}/chaintester/src"
    "${CMAKE_SOURCE_DIR}/libs/unittest-cpp/UnitTest++"
)
