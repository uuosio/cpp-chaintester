cmake_minimum_required(VERSION 3.21)

project(test-api-native)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

set(OPT_LEVEL -O0)
SET(CMAKE_C_FLAGS  "${OPT_LEVEL}")
SET(CMAKE_CXX_FLAGS  "${OPT_LEVEL} -std=c++17")
set(CMAKE_ASM_FLAGS "")

set(CMAKE_C_COMPILER "${CDT_PATH}/bin/clang-7")
set(CMAKE_CXX_COMPILER "${CDT_PATH}/bin/clang-7")

SET_PROPERTY(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

add_library( test_api_static SHARED ${CMAKE_CURRENT_SOURCE_DIR}/../test_api.cpp)
set_target_properties(test_api_static PROPERTIES CXX_VISIBILITY_PRESET hidden)

if (${PLATFORM} MATCHES APPLE)
    set(PLATFORM_OPTIONS  --target=x86_64-unknown-darwin-macho -mmacosx-version-min=10.13 -fno-stack-protector)
elseif(${PLATFORM} MATCHES LINUX)
    set(PLATFORM_OPTIONS -fPIC --target=x86_64-unknown-linux-gnu)
else()
    message( FATAL_ERROR "Unsupported platform: ${PLATFORM}")
endif()

target_compile_options(test_api_static PRIVATE
    -g
    ${OPT_LEVEL}
    ${PLATFORM_OPTIONS}
    --sysroot=${CDT_PATH}
    -D__eosio_cdt__
    # -D__eosio_cdt_major__=1
    # -D__eosio_cdt_minor__=7
    -D__eosio_cdt_patchlevel__=0 
    -Wunused-command-line-argument
    -m64
    -fno-builtin
    -mstackrealign
    -D__eosio_cdt_native__
    -DEOSIO_NATIVE
    -DLLP64
    -fno-threadsafe-statics
    -fno-exceptions
    -fno-rtti 
    -fmodules-ts
    -DBOOST_DISABLE_ASSERTS
    -DBOOST_EXCEPTION_DISABLE
    -mllvm
    -use-cfl-aa-in-codegen=both
    # -MF
)

target_include_directories(test_api_static PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CDT_PATH}/include/libcxx 
    ${CDT_PATH}/include/libc 
    ${CDT_PATH}/include 
    ${CDT_PATH}/include/eosiolib/capi 
    ${CDT_PATH}/include/eosiolib/native 
    ${CDT_PATH}/include/eosiolib/core 
    ${CDT_PATH}/include/eosiolib/contracts 
)

# target_link_options(test_api_static PRIVATE -L${CDT_PATH}/lib -lnative_c++ -lnative_c -lnative_rt)

target_link_libraries (test_api_static
    ${CMAKE_CURRENT_BINARY_DIR}/../../chainlib/native/libchain_static.a
    ${CMAKE_CURRENT_BINARY_DIR}/../../intrinsics/native/libintrinsics_static.a
    ${CMAKE_CURRENT_BINARY_DIR}/../../../libs/libc/native/libnative_c.a
    ${CMAKE_CURRENT_BINARY_DIR}/../../../libs/libc++/native/libnative_c++.a
    # ${CDT_PATH}/lib/libnative_c++.a
    # ${CDT_PATH}/lib/libnative_c.a
    # ${CDT_PATH}/lib/libnative_rt.a
)
