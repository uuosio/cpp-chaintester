add_subdirectory(hello)
add_subdirectory(multi_index_example)
add_subdirectory(new_intrinsics)

add_subdirectory(test_api/native)
add_subdirectory(test_api_db/native)
add_subdirectory(test_api_multi_index/native)

include(ExternalProject)
# if no cdt root is given use default path
if(CDT_ROOT STREQUAL "" OR NOT CDT_ROOT)
   find_package(cdt)
endif()

ExternalProject_Add(
   test-api-project
   SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_api
   BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/test_api
   CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CDT_ROOT}/lib/cmake/cdt/CDTWasmToolchain.cmake
   UPDATE_COMMAND ""
   PATCH_COMMAND ""
   TEST_COMMAND ""
   INSTALL_COMMAND ""
   BUILD_ALWAYS 1
)

ExternalProject_Add(
   test-api-multi-index-project
   SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_api_multi_index
   BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/test_api_multi_index
   CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CDT_ROOT}/lib/cmake/cdt/CDTWasmToolchain.cmake
   UPDATE_COMMAND ""
   PATCH_COMMAND ""
   TEST_COMMAND ""
   INSTALL_COMMAND ""
   BUILD_ALWAYS 1
)

ExternalProject_Add(
   activate-project
   SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/activate
   BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/activate
   CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CDT_ROOT}/lib/cmake/cdt/CDTWasmToolchain.cmake
   UPDATE_COMMAND ""
   PATCH_COMMAND ""
   TEST_COMMAND ""
   INSTALL_COMMAND ""
   BUILD_ALWAYS 1
)

ExternalProject_Add(
   bios-project
   SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/eosio.bios
   BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/eosio.bios
   CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CDT_ROOT}/lib/cmake/cdt/CDTWasmToolchain.cmake
   UPDATE_COMMAND ""
   PATCH_COMMAND ""
   TEST_COMMAND ""
   INSTALL_COMMAND ""
   BUILD_ALWAYS 1
)