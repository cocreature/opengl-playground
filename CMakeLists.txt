cmake_minimum_required (VERSION 2.6)
project (OpenGL-playground)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake/modules/")

set (CMAKE_CXX_STANDARD 14)

include(FindPkgConfig)
find_package(glm REQUIRED)
find_package(SOIL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
  "${PROJECT_SOURCE_DIR}/include"
  "${GLM_INCLUDE_DIRS}"
  "${SOIL_INCLUDE_DIRS}"
  "${GLEW_INCLUDE_DIRS}"
  # "${GLFW_INCLUDE_DIRS}"
  )

add_executable(opengl-playground src/main.cpp)

target_link_libraries(opengl-playground
  "${SOIL_LIBRARIES}"
  glfw
  "${GLEW_LIBRARIES}"
  "${OPENGL_gl_LIBRARY}"
  "${CMAKE_DL_LIBS}"
  )
