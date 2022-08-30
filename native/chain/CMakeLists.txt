add_library( chain_static
    src/crypto.cpp
    src/eosiolib.cpp
)

set_target_properties(chain_static PROPERTIES CXX_VISIBILITY_PRESET hidden)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(PLATFORM_OPTIONS "-fPIC")
endif()

target_compile_options(chain_static PRIVATE 
    -g
    -O0
    -fprofile-arcs -ftest-coverage
    -DEOSIO_NATIVE
    -Wno-unknown-attributes
    ${PLATFORM_OPTIONS}
)

target_include_directories(chain_static PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CDT_INCLUDE_PATH}
)

target_link_options(chain_static PRIVATE --fprofile-arcs -ftest-coverage)
