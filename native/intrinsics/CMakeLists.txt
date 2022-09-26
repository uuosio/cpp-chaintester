# library for linking shared native contract
add_library( intrinsics_native
    src/intrinsics.cpp
)

set_target_properties(intrinsics_native PROPERTIES CXX_VISIBILITY_PRESET hidden)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(PLATFORM_OPTIONS "-fPIC")
endif()

target_compile_options(intrinsics_native PRIVATE 
    -g
    -O0
    ${COVERAGE_OPTIONS}
    -DEOSIO_NATIVE
    -Wno-unknown-attributes
    ${PLATFORM_OPTIONS}
)

target_include_directories(intrinsics_native PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CDT_INCLUDE_PATH}
)

target_link_options(intrinsics_native PRIVATE ${COVERAGE_OPTIONS})
