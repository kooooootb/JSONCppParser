add_library(jsonparser STATIC Node.cpp Token.cpp Parser.cpp)

add_subdirectory(utility)

target_include_directories(jsonparser PUBLIC utility)
target_link_libraries(jsonparser PUBLIC jsonutility)
