add_subdirectory(hello)
add_subdirectory(multi_index_example)
add_subdirectory(new_intrinsics)

add_subdirectory(test_api/native)
add_subdirectory(test_api_db/native)
add_subdirectory(test_api_multi_index/native)

include(ExternalProject)
# if no cdt root is given use default path
if(EOSIO_CDT_ROOT STREQUAL "" OR NOT EOSIO_CDT_ROOT)
   find_package(eosio.cdt)
endif()

ExternalProject_Add(
   test-api-project
   SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_api
   BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/test_api
   CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${EOSIO_CDT_ROOT}/lib/cmake/eosio.cdt/EosioWasmToolchain.cmake
   UPDATE_COMMAND ""
   PATCH_COMMAND ""
   TEST_COMMAND ""
   INSTALL_COMMAND ""
   BUILD_ALWAYS 1
)

