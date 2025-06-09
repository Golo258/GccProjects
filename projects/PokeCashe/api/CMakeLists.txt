cmake_minimum_required(VERSION 3.14)
project(PokeAPI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include headers from "include" and "lib"
include_directories(include)
include_directories(lib)

# Find libpqxx
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

# Add source code
add_subdirectory(test)
add_subdirectory(src)