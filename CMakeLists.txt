cmake_minimum_required(VERSION 3.16.3)

project(chaintester)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
# add_subdirectory(libs/thrift)

execute_process(COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/find_cdt_path.py OUTPUT_VARIABLE CDT_PATH)
message(STATUS "++++++CDT_PATH:${CDT_PATH}")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(PLATFORM LINUX)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set(PLATFORM APPLE)
endif()

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
set_target_properties(thrift PROPERTIES IMPORTED_LOCATION  ${CMAKE_BINARY_DIR}/libs/thrift/lib/libthriftd${CMAKE_STATIC_LIBRARY_SUFFIX})

add_subdirectory(libs/Catch2)
add_subdirectory(chaintester)
add_subdirectory(tests)
