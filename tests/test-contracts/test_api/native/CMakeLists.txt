add_library( test_api_native ${CMAKE_CURRENT_SOURCE_DIR}/../test_api.cpp)

target_compile_options(test_api_native PRIVATE
    -g
    -O0
    ${COVERAGE_OPTIONS}
    -DEOSIO_NATIVE
    -Wno-attributes
    -Wno-unused-value
)

target_link_options(test_api_native PRIVATE ${COVERAGE_OPTIONS})

target_include_directories(test_api_native PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CDT_INCLUDE_PATH}
)
