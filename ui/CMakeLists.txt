set(SOURCES
    text.cpp
    uielement.cpp
)

add_library(ui ${SOURCES})

target_link_libraries(ui
    PUBLIC
        render
        engine
)

target_include_directories(ui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
