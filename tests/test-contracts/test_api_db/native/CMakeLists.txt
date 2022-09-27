add_library( test_api_db_native
    main.cpp
    ../test_api_db.cpp
)

set_target_properties(test_api_db_native PROPERTIES CXX_VISIBILITY_PRESET hidden)

target_compile_options(test_api_db_native PRIVATE 
    -g
    -O0
    ${COVERAGE_OPTIONS}
    -DEOSIO_NATIVE
    -Wno-attributes
    -Wno-deprecated-declarations
)

target_include_directories(test_api_db_native PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CDT_INCLUDE_PATH}
)

target_link_options(test_api_db_native PRIVATE ${COVERAGE_OPTIONS})

target_link_libraries (test_api_db_native
    chain_static
)
