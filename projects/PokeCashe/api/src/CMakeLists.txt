set(SOURCES
    main.cpp
    router.cpp
    handlers.cpp
    database.cpp
)

add_executable(poke_api ${SOURCES})

# add libpqxx 
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

# add headers path to  pqxx 
target_include_directories(poke_api PRIVATE ${PQXX_INCLUDE_DIRS})

# link lbirary  pqxx oraz pq (libpq = PostgreSQL client lib)
target_link_libraries(poke_api PRIVATE ${PQXX_LIBRARIES})
