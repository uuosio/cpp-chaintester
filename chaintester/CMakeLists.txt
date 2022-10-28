add_library(utils
    src/utils.cpp
    src/loader.cpp
)

target_compile_options(utils PRIVATE -DEOSIO_NATIVE -Wno-attributes)

target_include_directories(utils PRIVATE
    ${CDT_INCLUDE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library ( ipcchaintester 
    src/gen/Apply.cpp
    src/gen/ApplyRequest.cpp
    src/gen/IPCChainTester.cpp
    src/gen/PushActions.cpp
    src/gen/interfaces_types.cpp
    src/ipcchaintester.cpp
    src/vmapiclient.cpp
    src/intrinsics.cpp

    src/TServerFramework.cpp
    src/TSimpleServer.cpp
    src/TConnectedClient.cpp
)

if (APPLE)
else()
    set(PTHREAD_LIB pthread)
endif()
target_link_libraries ( ipcchaintester PUBLIC 
    utils
    softfloat
    intrinsics_native
    ${CMAKE_DL_LIBS}
    $<TARGET_FILE:Catch2>
    ${PTHREAD_LIB}
    thrift
)

target_include_directories(ipcchaintester PRIVATE
    "./gen"
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../native/intrinsics/include
    "${CMAKE_CURRENT_SOURCE_DIR}/../libs/thrift/lib/cpp/src"
    "${CMAKE_CURRENT_BINARY_DIR}/../libs/thrift"
    "${CMAKE_CURRENT_SOURCE_DIR}/../libs/rapidjson/include"
    "/usr/local/include"
)

add_dependencies(ipcchaintester Catch2)


set(SPECIAL_SRC_FILES
    src/ipcchaintester.cpp
    src/intrinsics.cpp
)

if (ENABLE_COVERAGE)
    set_property(SOURCE ${SPECIAL_SRC_FILES} PROPERTY COMPILE_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif()

target_compile_options(ipcchaintester PRIVATE -Wno-deprecated-declarations)

add_library ( chaintester 
    src/chaintester.cpp
    src/base58.cpp
)

target_link_libraries ( chaintester PUBLIC 
    ipcchaintester
)

target_include_directories(chaintester PUBLIC
    ${CDT_INCLUDE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    "${CMAKE_CURRENT_SOURCE_DIR}/../libs/Catch2/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/../libs/rapidjson/include"
    "${CMAKE_BINARY_DIR}/generated-includes"
)

target_compile_options(chaintester PRIVATE -DEOSIO_NATIVE -Wno-unknown-attributes -Wno-unused-value)
