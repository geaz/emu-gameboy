cmake_minimum_required(VERSION 3.0.0)
project(ggb VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists-AppleGL.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists-GLFW.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists-PortAudio.txt)

file(GLOB_RECURSE EMU_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/src/glad.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

include_directories(${GLFW_INCLUDE_DIR} ${PORTAUDIO_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include)

link_directories(${GLFW_LIBRARY_DIR} ${PORTAUDIO_LIBRARY_DIR})

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)
add_executable(ggb ${EMU_SOURCES})
add_dependencies(ggb glfw pta)
target_link_libraries(ggb glfw3 portaudio_static_x86 ${OPENGL_LIBRARIES} ${APPLE_LIBS})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/fonts/FiraMono-Regular.ttf FiraMono-Regular.ttf COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/shaders/rect.vshader shaders/rect.vshader COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/shaders/rect.fshader shaders/rect.fshader COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/shaders/text.vshader shaders/text.vshader COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/shaders/text.fshader shaders/text.fshader COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/shaders/texture.vshader shaders/texture.vshader COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/opengl/shaders/texture.fshader shaders/texture.fshader COPYONLY)