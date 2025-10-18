

cmake_minimum_required(VERSION 3.14)
project(cpp_notes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
    main.cpp
    src/namespaces.cpp
    src/structures.cpp
    src/classess.cpp
    src/collections.cpp
)

add_executable(
    main 
    ${SOURCES}
)

