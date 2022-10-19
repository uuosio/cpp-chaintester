add_subdirectory(native)

include(ExternalProject)
# if no cdt root is given use default path
if(EOSIO_CDT_ROOT STREQUAL "" OR NOT EOSIO_CDT_ROOT)
   find_package(cdt)
endif()

ExternalProject_Add(
   hello_project
   SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src
   BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/hello
   CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CDT_ROOT}/lib/cmake/cdt/CDTWasmToolchain.cmake
   UPDATE_COMMAND ""
   PATCH_COMMAND ""
   TEST_COMMAND ""
   INSTALL_COMMAND ""
   BUILD_ALWAYS 1
)
