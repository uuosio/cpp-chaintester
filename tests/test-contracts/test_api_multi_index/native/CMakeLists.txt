add_library( test_api_multi_index_native
    main.cpp
    ../test_api_multi_index.cpp
)

set_target_properties(test_api_multi_index_native PROPERTIES CXX_VISIBILITY_PRESET hidden)

target_compile_options(test_api_multi_index_native PRIVATE 
    -g
    -O0
    ${COVERAGE_OPTIONS}
    -DEOSIO_NATIVE
    -Wno-attributes
    -Wno-deprecated-declarations
)

target_include_directories(test_api_multi_index_native PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CDT_INCLUDE_PATH}
)

target_link_options(test_api_multi_index_native PRIVATE ${COVERAGE_OPTIONS})

target_link_libraries (test_api_multi_index_native
    chain_static
)
