cmake_minimum_required(VERSION 3.22)
project(JSONParser)

add_subdirectory(src)

install(DIRECTORY src
        DESTINATION .
        COMPONENT development
        FILES_MATCHING PATTERN "*.h")
