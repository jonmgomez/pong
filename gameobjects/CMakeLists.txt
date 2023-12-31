set(SOURCES
    ball.cpp
    gameobject.cpp
    opponent.cpp
    player.cpp
    scorearea.cpp
    scorecontroller.cpp
    settingsscreencontroller.cpp
    titlescreencontroller.cpp
    wall.cpp
    uimenu.cpp
)

add_library(gameobjects ${SOURCES})

target_link_libraries(gameobjects
    PUBLIC
        compile_flags
        render
        engine
        components
)

target_include_directories(gameobjects
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)


