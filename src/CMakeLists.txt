add_library(jsonparser STATIC Node.cpp Token.cpp)

add_subdirectory(utility)

target_include_directories(jsonparser PUBLIC "${CMAKE_CURRENT_LIST_DIR}/utility")
target_link_libraries(jsonparser PUBLIC utility)

target_include_directories(jsonparser PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")
