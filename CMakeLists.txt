cmake_minimum_required(VERSION 3.5)

project(raw-gfx)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW3 REQUIRED glfw3)

include_directories(${PROJECT_NAME} ${GLFW3_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} src/main.c src/glad.c src/shader.c)

target_link_libraries(${PROJECT_NAME} ${GLFW3_LIBRARIES})
