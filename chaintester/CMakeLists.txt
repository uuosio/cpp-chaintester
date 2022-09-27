add_library(utils
    src/utils.cpp
)

target_compile_options(utils PRIVATE -DEOSIO_NATIVE -Wno-attributes)

target_include_directories(utils PRIVATE
    ${CDT_INCLUDE_PATH}
)

add_library ( chaintester 
    src/gen/Apply.cpp
    src/gen/ApplyRequest.cpp
    src/gen/IPCChainTester.cpp
    src/gen/PushActions.cpp
    src/gen/interfaces_types.cpp
    src/chaintester.cpp
    src/vmapiclient.cpp
    src/intrinsics.cpp
    src/loader.cpp

    src/TServerFramework.cpp
    src/TSimpleServer.cpp
    src/TConnectedClient.cpp
)

if (APPLE)
else()
    set(PTHREAD_LIB pthread)
endif()
target_link_libraries ( chaintester PUBLIC 
    utils
    softfloat
    thrift
    intrinsics_native
    ${CMAKE_DL_LIBS}
    $<TARGET_FILE:Catch2>
    ${PTHREAD_LIB}
)

target_include_directories(chaintester PUBLIC
    "./gen"
    ${CMAKE_CURRENT_SOURCE_DIR}/../native/intrinsics/include
    "${CMAKE_CURRENT_SOURCE_DIR}/../libs/thrift/lib/cpp/src"
    "${CMAKE_CURRENT_BINARY_DIR}/../libs/thrift"
    "${CMAKE_CURRENT_SOURCE_DIR}/../libs/rapidjson/include"
    "/usr/local/include"
)

add_dependencies(chaintester thrift_external)

get_target_property(DEBUG_POSTFIX chaintester DEBUG_POSTFIX)
add_library(thrift STATIC IMPORTED)
set_target_properties(thrift PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/../libs/thrift/lib/libthrift${DEBUG_POSTFIX}${CMAKE_STATIC_LIBRARY_SUFFIX}")

add_custom_target(thrift-stub
        BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/libs/thrift/lib/libthrift${DEBUG_POSTFIX}${CMAKE_STATIC_LIBRARY_SUFFIX}
        COMMAND ""
        DEPENDS thrift_external
)

# target_compile_options(chaintester PRIVATE 
#     -g
#     -O3
#     -fprofile-arcs -ftest-coverage -fprofile-instr-generate -fcoverage-mapping
# )

# target_link_options(chaintester PRIVATE -fprofile-arcs -ftest-coverage -fprofile-instr-generate -fcoverage-mapping)

set(SPECIAL_SRC_FILES
    src/chaintester.cpp
    src/intrinsics.cpp
)

if (ENABLE_COVERAGE)
    set_property(SOURCE ${SPECIAL_SRC_FILES} PROPERTY COMPILE_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif()
