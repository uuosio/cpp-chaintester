set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(cdt)

add_contract(activate activate ${CMAKE_CURRENT_SOURCE_DIR}/src/activate.cpp)

target_include_directories(activate
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(activate
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

target_compile_options( activate PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
