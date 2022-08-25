if(EOSIO_CDT_ROOT STREQUAL "" OR NOT EOSIO_CDT_ROOT)
    find_package(eosio.cdt)
endif()
 
 
ExternalProject_Add(
    chainlib-project
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/native
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=Debug -DPLATFORM=${PLATFORM} -DCDT_PATH=${CDT_PATH} -DCMAKE_TOOLCHAIN_FILE=${EOSIO_CDT_ROOT}/lib/cmake/eosio.cdt/EosioWasmToolchain.cmake
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    TEST_COMMAND ""
    INSTALL_COMMAND ""
    BUILD_ALWAYS 0
)
