cmake_minimum_required(VERSION 3.16)
project(hydrogen_orbitals CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(hydrogen
  src/main.cpp
  src/app/application.cpp
  src/app/application.h
  src/render/renderer.cpp
  src/render/renderer.h
  src/hydrogen/hydrogen.cpp
  src/hydrogen/hydrogen.h
)

target_include_directories(hydrogen PRIVATE src)

target_link_libraries(hydrogen PRIVATE glfw GLEW::GLEW OpenGL::GL)
