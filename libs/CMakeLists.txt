include(ExternalProject)

add_subdirectory(Catch2)

if(EOSIO_CDT_ROOT STREQUAL "" OR NOT EOSIO_CDT_ROOT)
    find_package(eosio.cdt)
endif()

ExternalProject_Add(
   libc_native_project
   SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libc
   BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/libc/native
   CMAKE_ARGS -DCMAKE_BUILD_TYPE=Debug -DPLATFORM=${PLATFORM} -DCDT_PATH=${CDT_PATH} -DCMAKE_TOOLCHAIN_FILE=${EOSIO_CDT_ROOT}/lib/cmake/eosio.cdt/EosioWasmToolchain.cmake
   UPDATE_COMMAND ""
   PATCH_COMMAND ""
   TEST_COMMAND ""
   INSTALL_COMMAND ""
   BUILD_ALWAYS 1
)

ExternalProject_Add(
   libcxx_native_project
   SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libc++
   BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/libc++/native
   CMAKE_ARGS -DCMAKE_BUILD_TYPE=Debug -DPLATFORM=${PLATFORM} -DCDT_PATH=${CDT_PATH} -DCMAKE_TOOLCHAIN_FILE=${EOSIO_CDT_ROOT}/lib/cmake/eosio.cdt/EosioWasmToolchain.cmake
   UPDATE_COMMAND ""
   PATCH_COMMAND ""
   TEST_COMMAND ""
   INSTALL_COMMAND ""
   BUILD_ALWAYS 1
)
