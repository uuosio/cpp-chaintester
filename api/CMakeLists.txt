
add_library( cchaintester SHARED
    src/main.cpp
    src/test.cpp
    src/test_hello.cpp
)

if (APPLE)
      set(_symbols_list "${CMAKE_CURRENT_SOURCE_DIR}/symbols.list")
      set(LINK_FLAGS "${LINK_FLAGS} -Wl,-exported_symbols_list,'${_symbols_list}'")
else()
    set(_version_script "${CMAKE_CURRENT_SOURCE_DIR}/version.script")
    set(LINK_FLAGS "${LINK_FLAGS} -Wl,--version-script,\"${_version_script}\"")
endif (APPLE)

set_target_properties(cchaintester  PROPERTIES LINK_FLAGS "${LINK_FLAGS}")

target_compile_options( cchaintester PRIVATE 
    -g
    -O0
    -DEOSIO_NATIVE
    -Wno-attributes
    -Wno-deprecated-declarations
    -Wno-unused-value
)

target_link_options( cchaintester PRIVATE ${COVERAGE_OPTIONS})

target_link_libraries( cchaintester
    intrinsics_native
    chaintester
)

add_dependencies( cchaintester chaintester)

target_include_directories( cchaintester PUBLIC
"${CMAKE_CURRENT_SOURCE_DIR}/src"
"${CMAKE_CURRENT_BINARY_DIR}"
${CMAKE_CURRENT_SOURCE_DIR}/../native/intrinsics/include
"${CMAKE_BINARY_DIR}/generated-includes"
)

configure_file(src/generated.h.in ${CMAKE_CURRENT_BINARY_DIR}/generated.h @ONLY )
