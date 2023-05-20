project(example)

add_executable(example example.cpp)
target_link_libraries(example PRIVATE jsonparser)

set_target_properties(example PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")
