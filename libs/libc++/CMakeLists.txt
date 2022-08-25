cmake_minimum_required(VERSION 3.21)

project(libcxx_native)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

set(OPT_LEVEL -O0)
SET(CMAKE_C_FLAGS  "${OPT_LEVEL}")
SET(CMAKE_CXX_FLAGS  "${OPT_LEVEL} -std=c++17")
set(CMAKE_ASM_FLAGS "")

set(CMAKE_C_COMPILER "${CDT_PATH}/bin/clang-7")
set(CMAKE_CXX_COMPILER "${CDT_PATH}/bin/clang-7")

SET_PROPERTY(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

SET(SRC_FILENAMES algorithm.cpp any.cpp bind.cpp condition_variable.cpp functional.cpp
                  future.cpp ios.cpp iostream.cpp locale.cpp memory.cpp mutex.cpp new.cpp optional.cpp
                  regex.cpp stdexcept.cpp string.cpp strstream.cpp system_error.cpp exception.cpp
                  typeinfo.cpp utility.cpp valarray.cpp variant.cpp vector.cpp eosio.cpp)

SET(SRC_FILES "")
FOREACH(FN ${SRC_FILENAMES})
   LIST(APPEND SRC_FILES "libcxx/src/${FN}")
ENDFOREACH(FN)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-everything")

add_library(native_c++
            ${SRC_FILES})


if (${PLATFORM} MATCHES APPLE)
    set(PLATFORM_OPTIONS  --target=x86_64-unknown-darwin-macho -mmacosx-version-min=10.13 -fno-stack-protector)
elseif(${PLATFORM} MATCHES LINUX)
    set(PLATFORM_OPTIONS -fPIC --target=x86_64-unknown-linux-gnu)
else()
    message( FATAL_ERROR "Unsupported platform: ${PLATFORM}")
endif()

target_compile_options(native_c++ PRIVATE 
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

target_include_directories(native_c++
                           PUBLIC 
                           ${CMAKE_CURRENT_SOURCE_DIR}/libcxx/include
                           ${CMAKE_CURRENT_SOURCE_DIR}/../libc/musl/include
                           ${CMAKE_CURRENT_SOURCE_DIR}/../libc/musl/src/internal
                           ${CMAKE_CURRENT_SOURCE_DIR}/../libc/musl/src/crypt
                           ${CMAKE_CURRENT_SOURCE_DIR}/../libc/musl/arch/eos)


# target_link_libraries(native_c++ native_c)
# target_compile_options(native_c++ PUBLIC -allow-sse)

# add_custom_command( TARGET native_c++ POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:native_c++> ${BASE_BINARY_DIR}/lib )

# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libcxx/include/ DESTINATION ${BASE_BINARY_DIR}/include/libcxx)
