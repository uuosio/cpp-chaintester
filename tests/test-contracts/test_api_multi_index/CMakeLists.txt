set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(cdt)

add_contract( test_api_multi_index test_api_multi_index test_api_multi_index.cpp )
target_include_directories( test_api_multi_index PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include )

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/test_api_multi_index.abi  ${CMAKE_CURRENT_BINARY_DIR}/test_api_multi_index.abi  COPYONLY )
