cmake_minimum_required(VERSION 3.21)
project(libc_native)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

set(OPT_LEVEL -O0)
SET(CMAKE_C_FLAGS  "${OPT_LEVEL}")
SET(CMAKE_CXX_FLAGS  "${OPT_LEVEL} -std=c++17")
set(CMAKE_ASM_FLAGS "")

set(CMAKE_C_COMPILER "${CDT_PATH}/bin/clang-7")
set(CMAKE_CXX_COMPILER "${CDT_PATH}/bin/clang-7")

SET_PROPERTY(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

file(GLOB CRYPT_SOURCES  "musl/src/crypt/*.c")
file(GLOB CTYPE_SOURCES  "musl/src/ctype/*.c")
file(GLOB ENV_SOURCES  "musl/src/env/*.c")
file(GLOB ERRNO_SOURCES  "musl/src/errno/*.c")
file(GLOB EXIT_SOURCES  "musl/src/exit/*.c")
file(GLOB LOCALE_SOURCES "musl/src/locale/*.c")
file(GLOB MATH_SOURCES  "musl/src/math/*.c")
file(GLOB MBYTE_SOURCES  "musl/src/multibyte/*.c")
file(GLOB MISC_SOURCES "musl/src/misc/*.c")
file(GLOB SEARCH_SOURCES "musl/src/search/*.c")
file(GLOB STDIO_SOURCES "musl/src/stdio/*.c")
file(GLOB STDLIB_SOURCES "musl/src/stdlib/*.c")
file(GLOB STRING_SOURCES "musl/src/string/*.c")
#file(GLOB TIME_SOURCES "musl/src/time/*.c")
file(GLOB THREAD_SOURCES "musl/src/thread/*.c") #only for __lock __unlock

set(INTERNAL_SOURCES musl/src/internal/floatscan.c musl/src/internal/intscan.c musl/src/internal/shgetc.c musl/src/internal/libc.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-everything -allow-sse")

file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/musl/include/*.h"
                  "${CMAKE_CURRENT_SOURCE_DIR}/musl/src/internal/*.h"
                  "${CMAKE_CURRENT_SOURCE_DIR}/musl/arch/eos/*.h")

add_library(native_c 
            ${CRYPT_SOURCES} 
            ${CTYPE_SOURCES}
            ${ENV_SOURCES}
            ${ERRNO_SOURCES}
            ${EXIT_SOURCES}
            ${INTERNAL_SOURCES}
            ${LOCALE_SOURCES}
            ${MATH_SOURCES}
            ${MBYTE_SOURCES}
            ${MISC_SOURCES}
            ${SEARCH_SOURCES}
            ${STDIO_SOURCES}
            ${STDLIB_SOURCES}
            ${STRING_SOURCES}
            ${TIME_SOURCES}
            ${THREAD_SOURCES}
            "musl/src/malloc/posix_memalign.c"
            "musl/src/malloc/memalign.c"
            ${HEADERS})

if (${PLATFORM} MATCHES APPLE)
    set(PLATFORM_OPTIONS  --target=x86_64-unknown-darwin-macho -mmacosx-version-min=10.13 -fno-stack-protector)
elseif(${PLATFORM} MATCHES LINUX)
    set(PLATFORM_OPTIONS -fPIC --target=x86_64-unknown-linux-gnu)
else()
    message( FATAL_ERROR "Unsupported platform: ${PLATFORM}")
endif()

target_compile_options(native_c PRIVATE 
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
            
target_include_directories(native_c 
                           PUBLIC 
                           ${CMAKE_CURRENT_SOURCE_DIR}/musl/include
                           ${CMAKE_CURRENT_SOURCE_DIR}/musl/src/internal
                           ${CMAKE_CURRENT_SOURCE_DIR}/musl/src/crypt
                           ${CMAKE_CURRENT_SOURCE_DIR}/musl/arch/eos
                           ${CMAKE_SOURCE_DIR})

# add_custom_command( TARGET native_c POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:native_c> ${BASE_BINARY_DIR}/lib )

# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/musl/include/ DESTINATION ${BASE_BINARY_DIR}/include/libc/)
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/musl/src/internal/ DESTINATION ${BASE_BINARY_DIR}/include/libc/)
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/musl/arch/eos/ DESTINATION ${BASE_BINARY_DIR}/include/libc/)
