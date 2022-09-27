cmake_minimum_required(VERSION 3.16.3)

project(chaintester)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Set debug library postfix")

option(BUILD_LIBRARIES "Build Thrift libraries" ON)
option(WITH_CPP "Build C++ Thrift library" ON)
option(BUILD_COMPILER "Build Thrift compiler" OFF)
option(WITH_AS3 "Build ActionScript 3 Thrift Library" OFF)
option(WITH_C_GLIB "Build C (GLib) Thrift library" OFF)
option(WITH_JAVA "Build Java Thrift library" OFF)
option(WITH_JAVASCRIPT "Build Javascript Thrift library" OFF)
option(WITH_NODEJS "Build NodeJS Thrift library" OFF)
option(WITH_PYTHON "Build Python Thrift library" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(WITH_MT "Build using the static runtime 'MT' instead of the shared DLL-specific runtime 'MD' (MSVC only)" OFF)
option(BUILD_TESTING "Build with unit tests" OFF)

# option(WITH_ZLIB "Build with ZLIB support" OFF)
# option(WITH_LIBEVENT "Build with libevent support" OFF)

add_subdirectory(libs/thrift)

# include(ExternalProject)

# ExternalProject_Add(
#     thrift_external
#     SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/thrift
#     BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/libs/thrift
#     CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DBUILD_TESTING=FALSE -DBUILD_COMPILER=FALSE -DBUILD_JAVA=FALSE -DBUILD_JAVASCRIPT=FALSE -DBUILD_NODEJS=FALSE -DBUILD_NODEJS=FALSE -DBUILD_PYTHON=FALSE
#     UPDATE_COMMAND ""
#     PATCH_COMMAND ""
#     TEST_COMMAND ""
#     INSTALL_COMMAND ""
#     BUILD_ALWAYS 1
# )

set(CDT_INCLUDE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/cdt/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/cdt/include/eosiolib/capi
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/cdt/include/eosiolib/native
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/cdt/include/eosiolib/core
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/cdt/include/eosiolib/contracts
)

if (ENABLE_COVERAGE)
    set(COVERAGE_OPTIONS -fprofile-arcs -ftest-coverage)
else()
    set(COVERAGE_OPTIONS )
endif()

add_subdirectory(libs)
add_subdirectory(native)
add_subdirectory(chaintester)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

