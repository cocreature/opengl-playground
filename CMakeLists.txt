cmake_minimum_required (VERSION 2.6)
project (OpenGL-playground)

set (CMAKE_CXX_STANDARD 14)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED)
find_package(glm REQUIRED)

include_directories(
  "${PROJECT_SOURCE_DIR}/include"
  "${SDL2_INCLUDE_DIRS}"
  "${GLM_INCLUDE_DIRS}"
  )

add_executable(opengl-playground
  src/main.cpp
  src/gl3w.c
  src/renderer.cpp
  src/scene.cpp
  src/shader.cpp
  )

target_link_libraries(opengl-playground
  "${SDL2_LIBRARIES}"
  "${CMAKE_DL_LIBS}"
  )
