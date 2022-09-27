cmake_minimum_required(VERSION 3.16.3)

project(chaintester)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
# add_subdirectory(libs/thrift)

include(ExternalProject)

ExternalProject_Add(
    thrift_external
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/thrift
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/libs/thrift
    CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DBUILD_TESTING=FALSE -DBUILD_COMPILER=FALSE -DBUILD_JAVA=FALSE -DBUILD_JAVASCRIPT=FALSE -DBUILD_NODEJS=FALSE -DBUILD_NODEJS=FALSE -DBUILD_PYTHON=FALSE
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    TEST_COMMAND ""
    INSTALL_COMMAND ""
    BUILD_ALWAYS 1
)

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

