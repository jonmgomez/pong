set(SOURCES
    config.cpp
    difficulty.cpp
)

add_library(settings ${SOURCES})

target_link_libraries(settings
    PUBLIC
        compile_flags
        engine
)

target_include_directories(settings
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
