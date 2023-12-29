set(SOURCES
    applicationwindow.cpp
    audiomixer.cpp
    behavior.cpp
    circle.cpp
    colliderbox.cpp
    collisionmanager.cpp
    component.cpp
    componentmanager.cpp
    config.cpp
    difficulty.cpp
    engine.cpp
    input.cpp
    logger.cpp
    mesh.cpp
    playingsound.cpp
    pong.cpp
    pongscenes.cpp
    random.cpp
    realtimelogger.cpp
    rectangle.cpp
    sound.cpp
    textcharacter.cpp
    timer.cpp
    uieventmanager.cpp
)

add_library(engine ${SOURCES})

target_link_libraries(engine
    PUBLIC
        render
        gameobjects
        ui
        fmt::fmt
        concurrentqueue
        portaudio_static
        AudioFile
)

target_include_directories(engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
