set(SOURCES
    circle.cpp
    font.cpp
    fontbank.cpp
    image.cpp
    rectangle.cpp
    textcharacter.cpp
)

add_library(graphics ${SOURCES})

target_link_libraries(graphics
    PUBLIC
        compile_flags
        engine
        render
        stb
)

target_include_directories(graphics
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
