

cmake_minimum_required(VERSION 3.14)
project(cpp_notes)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(main main.cpp src/namespace_notes.cpp)