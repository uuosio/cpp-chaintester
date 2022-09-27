add_library( new_intrinsics_native
    ../src/new_intrinsics.cpp
    ../src/main.cpp
)

set_target_properties(new_intrinsics_native PROPERTIES CXX_VISIBILITY_PRESET hidden)

target_compile_options(new_intrinsics_native PRIVATE 
    -g
    -O0
    ${COVERAGE_OPTIONS}
    -DEOSIO_NATIVE
    -Wno-attributes
)

target_include_directories(new_intrinsics_native PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CDT_INCLUDE_PATH}
)

target_link_options(new_intrinsics_native PRIVATE ${COVERAGE_OPTIONS})

target_link_libraries (new_intrinsics_native
    chain_static
)
