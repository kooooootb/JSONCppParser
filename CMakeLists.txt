cmake_minimum_required(VERSION 3.22)
project(JSONParser)

add_subdirectory(src)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_LIST_DIR})
    add_subdirectory(example)
endif()
