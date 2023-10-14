add_library(glew ${CMAKE_CURRENT_SOURCE_DIR}/src/glew.c ${CMAKE_CURRENT_SOURCE_DIR}/src/glewinfo.c ${CMAKE_CURRENT_SOURCE_DIR}/src/visualinfo.c)

target_include_directories(glew PUBLIC include)
target_compile_definitions(glew PUBLIC GLEW_STATIC)
