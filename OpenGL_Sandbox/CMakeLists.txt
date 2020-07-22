cmake_minimum_required(VERSION 3.16)
project(OpenGL_Sandbox)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

## add extra include directories
include_directories(OpenGL_Sandbox ${PROJECT_SOURCE_DIR}/src)
include_directories(OpenGL_Sandbox ${PROJECT_SOURCE_DIR}/src/vendor)
include_directories(OpenGL_Sandbox ${PROJECT_SOURCE_DIR}/src/framework)

include_directories(OpenGL_Sandbox ${PROJECT_SOURCE_DIR}/dep/GLFW/include)
link_directories(OpenGL_Sandbox ${PROJECT_SOURCE_DIR}/dep/GLFW/lib-vc2019)

include_directories(OpenGL_Sandbox ${PROJECT_SOURCE_DIR}/dep/GLEW/include)
link_directories(OpenGL_Sandbox ${PROJECT_SOURCE_DIR}/dep/GLEW/lib/Release/x64)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(OpenGL_Sandbox
        src/Main.cpp
        src/Vector.h
        src/framework/Renderer.cpp
        src/framework/Renderer.h
        src/framework/VertexBuffer.cpp
        src/framework/VertexBuffer.h
        src/framework/IndexBuffer.cpp
        src/framework/IndexBuffer.h
        src/framework/VertexArray.cpp
        src/framework/VertexArray.h
        src/framework/VertexBufferLayout.cpp
        src/framework/VertexBufferLayout.h
        src/framework/Shader.cpp
        src/framework/Shader.h
        src/framework/Mesh.cpp
        src/framework/Mesh.h
        src/vendor/stb_image/stb_image.h
        src/vendor/stb_image/stb_image.cpp
        src/framework/Texture.cpp
        src/framework/Texture.h
        src/framework/Material.cpp
        src/framework/Material.h src/framework/AppWindow.cpp src/framework/AppWindow.h)

# specify the dependency on an extra library
target_link_libraries(OpenGL_Sandbox glfw3.lib glew32s.lib ${OPENGL_LIBRARIES})

add_compile_definitions(GLEW_STATIC)

IF (CMAKE_DEBUG)
    add_compile_definitions(CMAKE_DEBUG)
ENDIF(CMAKE_DEBUG)