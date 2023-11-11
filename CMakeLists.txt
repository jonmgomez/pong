cmake_minimum_required(VERSION 3.21)

project(pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

add_library(compile_flags INTERFACE)

# I would use /Wall here but unfortunately the msvc headers trigger some pedantic warnings,
# and I would like to keep /WX as well. Since I don't have an easy way to ignore the warnings
# for the system libraries, just use /W4. Seems like /Wall has some weird extra warnings anyways.
target_compile_options(compile_flags INTERFACE /W4 /WX /MP)

target_compile_definitions(compile_flags INTERFACE
    $<$<CONFIG:Debug>:
        DEBUG=1
    >
)

add_subdirectory(tps)

add_subdirectory(render)
add_subdirectory(engine)
add_subdirectory(gameobjects)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        render
        engine
        compile_flags
)
