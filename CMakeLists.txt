cmake_minimum_required (VERSION 2.6)
project (OpenGL-playground)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake/modules/")

set (CMAKE_CXX_STANDARD 14)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
find_package(glm REQUIRED)

include_directories(
  "${PROJECT_SOURCE_DIR}/include"
  "${SDL2_INCLUDE_DIRS}"
  "${SDL2_IMAGE_INCLUDE_DIRS}"
  "${GLM_INCLUDE_DIRS}"
  )

add_library(gl3w
  src/gl3w.c
  )

add_executable(opengl-playground
  src/main.cpp
  src/renderer.cpp
  src/scene.cpp
  src/shaderset.cpp
  src/simulation.cpp
  src/flythrough_camera.cpp
  )

target_link_libraries(opengl-playground
  "${SDL2_LIBRARIES}"
  "${SDL2_IMAGE_LIBRARIES}"
  gl3w
  "${CMAKE_DL_LIBS}"
  )
