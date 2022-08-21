cmake_minimum_required(VERSION 3.16.3)

project(chaintester)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# add_subdirectory(libs/unittest-cpp)
# add_subdirectory(libs/thrift)

include(ExternalProject)

ExternalProject_Add(
    thrift_external
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/thrift
    BINARY_DIR ${CMAKE_BINARY_DIR}/libs/thrift
    CMAKE_ARGS -DBUILD_TESTING=FALSE -DBUILD_COMPILER=FALSE -DBUILD_JAVA=FALSE -DBUILD_JAVASCRIPT=FALSE -DBUILD_NODEJS=FALSE -DBUILD_NODEJS=FALSE -DBUILD_PYTHON=FALSE
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    TEST_COMMAND ""
    INSTALL_COMMAND ""
    BUILD_ALWAYS 1
)

add_library(thrift STATIC IMPORTED)
set_target_properties(thrift PROPERTIES IMPORTED_LOCATION  ${CMAKE_BINARY_DIR}/libs/thrift/lib/libthriftd.a)

add_subdirectory(chaintester)
add_subdirectory(tests)
