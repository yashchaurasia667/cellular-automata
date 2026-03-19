cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ca LANGUAGES C CXX)
find_package(OpenGL REQUIRED)

set(INCLUDE "/usr/local/include/")
set(SRC     "/usr/local/src")
set(LIB     "/usr/local/lib")

# set(INCLUDE     "${CMAKE_CURRENT_SOURCE_DIR}/../include")
# set(LIB         "${CMAKE_CURRENT_SOURCE_DIR}/../lib")
# set(SRC         "${CMAKE_CURRENT_SOURCE_DIR}")

# ---- Library with actual compiled code ----
add_library(depends STATIC
  "${SRC}/glad.c"
  "${SRC}/learnOpengl/shader.cpp"
  "${SRC}/learnOpengl/vertexBuffer.cpp"
  "${SRC}/learnOpengl/vertexBufferLayout.cpp"
  "${SRC}/learnOpengl/indexBuffer.cpp"
  "${SRC}/learnOpengl/vertexArray.cpp"
  "${SRC}/learnOpengl/camera.cpp"
  "${SRC}/learnOpengl/texture.cpp"
  "${SRC}/learnOpengl/utils.cpp"
  "${SRC}/learnOpengl/mesh.cpp"
  "${SRC}/learnOpengl/model.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/automata.cpp"
)
target_include_directories(depends
  PUBLIC
  "${INCLUDE}"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/"
)
target_compile_options(depends
  PRIVATE
  -Wall
  -g
)
target_link_libraries(depends
  PUBLIC
  OpenGL::GL
  "${LIB}/libglfw3.a"
  "${LIB}/libassimp.a"
  minizip dl z pthread
  X11 Xrandr Xi
)
# ---- Executable ----
add_executable(
  ${PROJECT_NAME}
  "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  depends
)