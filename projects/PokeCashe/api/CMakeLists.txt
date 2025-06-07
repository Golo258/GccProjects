
cmake_minimum_required(VERSION 3.14)
project(PokeAPI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# catalogs with headers files
include_directories(include)
include_directories(lib)

# catalogs with source files
add_subdirectory(src)

