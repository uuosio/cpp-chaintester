cmake_minimum_required(VERSION 3.21)

project(hello)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

set(OPT_LEVEL -O0)
SET(CMAKE_C_FLAGS  "${OPT_LEVEL}")
SET(CMAKE_CXX_FLAGS  "${OPT_LEVEL} -std=c++17")
set(CMAKE_ASM_FLAGS "")

set(CMAKE_C_COMPILER "${EOSIO_CDT_ROOT}/opt/eosio.cdt/bin/clang-7")
set(CMAKE_CXX_COMPILER "${EOSIO_CDT_ROOT}/opt/eosio.cdt/bin/clang-7")

add_library( hello_static 
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/hello.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/main.cpp
)

if (${PLATFORM} MATCHES APPLE)
    set(PLATFORM_OPTIONS  --target=x86_64-unknown-darwin-macho -mmacosx-version-min=10.13 -fno-stack-protector)
elseif(${PLATFORM} MATCHES LINUX)
    set(PLATFORM_OPTIONS --target=x86_64-unknown-linux-gnu)
else()
    message( FATAL_ERROR "Unsupported platform: ${PLATFORM}")
endif()

target_compile_options(hello_static PRIVATE 
    -g
    ${OPT_LEVEL}
    ${PLATFORM_OPTIONS}
    --sysroot=${EOSIO_CDT_ROOT}/opt/eosio.cdt/bin/..
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

target_include_directories(hello_static PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${EOSIO_CDT_ROOT}/opt/eosio.cdt/bin/../include/libcxx 
    ${EOSIO_CDT_ROOT}/opt/eosio.cdt/bin/../include/libc 
    ${EOSIO_CDT_ROOT}/opt/eosio.cdt/bin/../include 
    ${EOSIO_CDT_ROOT}/opt/eosio.cdt/bin/../include/eosiolib/capi 
    ${EOSIO_CDT_ROOT}/opt/eosio.cdt/bin/../include/eosiolib/native 
    ${EOSIO_CDT_ROOT}/opt/eosio.cdt/bin/../include/eosiolib/core 
    ${EOSIO_CDT_ROOT}/opt/eosio.cdt/bin/../include/eosiolib/contracts 
)
