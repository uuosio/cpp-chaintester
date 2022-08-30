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
    -fprofile-arcs -ftest-coverage
    -DEOSIO_NATIVE
    -Wno-unknown-attributes
    ${PLATFORM_OPTIONS}
)

target_include_directories(intrinsics_native PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/libs/cdt/include
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/capi
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/native
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/core
    ${CMAKE_SOURCE_DIR}/libs/cdt/include/eosiolib/contracts

)

target_link_options(intrinsics_native PRIVATE -fprofile-arcs -ftest-coverage)
