include(ExternalProject)
# if no cdt root is given use default path
if(EOSIO_CDT_ROOT STREQUAL "" OR NOT EOSIO_CDT_ROOT)
   find_package(eosio.cdt)
endif()

ExternalProject_Add(
   hello_project
   SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src
   BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/hello
   CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${EOSIO_CDT_ROOT}/lib/cmake/eosio.cdt/EosioWasmToolchain.cmake
   UPDATE_COMMAND ""
   PATCH_COMMAND ""
   TEST_COMMAND ""
   INSTALL_COMMAND ""
   BUILD_ALWAYS 1
)

if (APPLE)
   set(PLATFORM APPLE)
elseif(LINUX)
   set(PLATFORM LINUX)
elseif(WIN32)
   set(PLATFORM WIN32)
endif()

ExternalProject_Add(
   hello_native_project
   SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/native
   BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/native
   CMAKE_ARGS -DCMAKE_BUILD_TYPE=Debug -DPLATFORM=${PLATFORM} -DEOSIO_CDT_ROOT=${EOSIO_CDT_ROOT} -DCMAKE_TOOLCHAIN_FILE=${EOSIO_CDT_ROOT}/lib/cmake/eosio.cdt/EosioWasmToolchain.cmake
   UPDATE_COMMAND ""
   PATCH_COMMAND ""
   TEST_COMMAND ""
   INSTALL_COMMAND ""
   BUILD_ALWAYS 1
)
