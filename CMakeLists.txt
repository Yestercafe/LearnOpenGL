cmake_minimum_required(VERSION 3.28)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 20)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

file(COPY "./assets" DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(libs)

add_subdirectory(Triangle)
add_subdirectory(Textures)
