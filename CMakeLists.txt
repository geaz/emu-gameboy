cmake_minimum_required(VERSION 3.0.0)
project(emu-gameboy VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists-AppleGL.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists-GLFW.txt)

file(GLOB_RECURSE EMU_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/src/glad.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

include_directories(${GLFW_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include)

link_directories(${GLFW_LIBRARY_DIR})

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)
add_executable(emu-gameboy ${EMU_SOURCES})
add_dependencies(emu-gameboy glfw)
target_link_libraries(emu-gameboy glfw3 ${OPENGL_LIBRARIES} ${APPLE_LIBS})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/fonts/FiraMono-Regular.ttf FiraMono-Regular.ttf COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/shaders/rect.vshader shaders/rect.vshader COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/shaders/rect.fshader shaders/rect.fshader COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/shaders/text.vshader shaders/text.vshader COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/shaders/text.fshader shaders/text.fshader COPYONLY)