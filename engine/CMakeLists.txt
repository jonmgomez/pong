set(SOURCES
    circle.cpp
    colliderbox.cpp
    collisionmanager.cpp
    config.cpp
    difficulty.cpp
    input.cpp
    logger.cpp
    mesh.cpp
    pong.cpp
    random.cpp
    realtimelogger.cpp
    rectangle.cpp
    timer.cpp
)

add_library(engine ${SOURCES})

target_link_libraries(engine
    PUBLIC
        render
        gameobjects
        fmt::fmt
        concurrentqueue
)

target_include_directories(engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
