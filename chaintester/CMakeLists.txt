add_library ( chaintester 
    src/gen/Apply.cpp
    src/gen/ApplyRequest.cpp
    src/gen/IPCChainTester.cpp
    src/gen/PushActions.cpp
    src/gen/interfaces_types.cpp
    src/chaintester.cpp
    src/intrinsics.cpp
    src/loader.cpp

    src/TServerFramework.cpp
    src/TSimpleServer.cpp
    src/TConnectedClient.cpp
)

target_link_libraries ( chaintester PUBLIC thrift ${CMAKE_DL_LIBS})

target_include_directories(chaintester PUBLIC
    "./gen"
    "${CMAKE_SOURCE_DIR}/libs/thrift/lib/cpp/src"
    "${CMAKE_SOURCE_DIR}/build/libs/thrift"
    "${CMAKE_SOURCE_DIR}/libs/rapidjson/include"
    "/usr/local/include"
)

add_dependencies(chaintester thrift_external)

