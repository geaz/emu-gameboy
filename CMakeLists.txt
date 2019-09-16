cmake_minimum_required(VERSION 3.0.0)
project(emu-gameboy VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists-GLFW.txt)

file(GLOB_RECURSE EMU_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/src/glad.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

include_directories(${GLFW_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include)

link_directories(${GLFW_LIBRARY_DIR})

add_executable(emu-gameboy ${EMU_SOURCES})
add_dependencies(emu-gameboy glfw)
target_link_libraries(emu-gameboy glfw3 ${OPENGL_LIBRARIES})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fonts/Minecraft.ttf Minecraft.ttf COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/rect.vshader shaders/rect.vshader COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/rect.fshader shaders/rect.fshader COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/text.vshader shaders/text.vshader COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/text.fshader shaders/text.fshader COPYONLY)