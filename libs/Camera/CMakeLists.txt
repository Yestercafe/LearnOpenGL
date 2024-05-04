project(Camera)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
    ../GL
)

file(GLOB SOURCES "*.cpp")

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad::glad
    glm::glm
    spdlog::spdlog_header_only
    GL
)
