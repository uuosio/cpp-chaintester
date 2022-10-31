add_library( hello_native
    ../src/hello.cpp
    main.cpp
)

set_target_properties(hello_native PROPERTIES CXX_VISIBILITY_PRESET hidden)

target_compile_options(hello_native PRIVATE 
    ${COVERAGE_OPTIONS}
    -DEOSIO_NATIVE
    -Wno-attributes
    -Wno-unused-value
)

target_include_directories(hello_native PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CDT_INCLUDE_PATH}
)

target_link_options(hello_native PRIVATE ${COVERAGE_OPTIONS})

target_link_libraries (hello_native
    chain_static
)


add_library( hello_native_shared SHARED
    ../src/hello.cpp
    main.cpp
)

set_target_properties(hello_native_shared PROPERTIES CXX_VISIBILITY_PRESET hidden)

target_compile_options(hello_native_shared PRIVATE 
    -g
    -O0
    ${COVERAGE_OPTIONS}
    -DEOSIO_NATIVE
    -Wno-attributes
    -Wno-unused-value
)

target_include_directories(hello_native_shared PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CDT_INCLUDE_PATH}
)

target_link_options(hello_native_shared PRIVATE ${COVERAGE_OPTIONS})

target_link_libraries (hello_native_shared
    chain_static
    intrinsics_native
)
