enable_testing()
include(GoogleTest)


add_executable(poke_test
    poke_test.cpp
    ${PROJECT_SOURCE_DIR}/src/database.cpp
)

target_link_libraries(poke_test PRIVATE ${PQXX_LIBRARIES} gtest gtest_main pthread)
target_include_directories(poke_test PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PQXX_INCLUDE_DIRS}
)

gtest_discover_tests(poke_test)