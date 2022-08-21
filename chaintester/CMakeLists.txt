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
    "../libs/thrift/lib/cpp/src"
    "../build/libs/thrift"
    "/usr/local/include"
    # "/usr/local/Cellar/eosio.cdt/1.7.0/opt/eosio.cdt/include"
)

add_dependencies(chaintester thrift_external)

