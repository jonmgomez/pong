set(SOURCES
    logger.cpp
    realtimelogger.cpp
)

add_library(logger ${SOURCES})

target_link_libraries(logger
    PUBLIC
        compile_flags
        spdlog::spdlog
        fmt::fmt
        engine
)

target_include_directories(logger
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
