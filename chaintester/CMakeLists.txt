add_library ( chaintester 
    src/gen/Apply.cpp
    src/gen/ApplyRequest.cpp
    src/gen/IPCChainTester.cpp
    src/gen/PushActions.cpp
    src/gen/interfaces_types.cpp
    src/chaintester.cpp
)

target_link_libraries ( chaintester thrift )

target_include_directories(chaintester PUBLIC
    "./gen"
    "${CMAKE_SOURCE_DIR}/libs/thrift/lib/cpp/src"
    "${CMAKE_SOURCE_DIR}/build/libs/thrift"
    "${CMAKE_SOURCE_DIR}/libs/rapidjson/include"
    "/usr/local/include"
)

add_dependencies(chaintester thrift_external)

