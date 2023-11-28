set(SOURCES
    audio.cpp
    circle.cpp
    colliderbox.cpp
    collisionmanager.cpp
    config.cpp
    difficulty.cpp
    input.cpp
    logger.cpp
    mesh.cpp
    playingsound.cpp
    pong.cpp
    random.cpp
    realtimelogger.cpp
    rectangle.cpp
    sound.cpp
    text.cpp
    textcharacter.cpp
    timer.cpp
)

add_library(engine ${SOURCES})

target_link_libraries(engine
    PUBLIC
        render
        gameobjects
        fmt::fmt
        concurrentqueue
        portaudio_static
        AudioFile
)

target_include_directories(engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
