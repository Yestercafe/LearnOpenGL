project(Textures)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
    ../libs/ShaderProgram
    ../libs/StbImage
)

file(GLOB SOURCES "*.cpp")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vertexShader.glsl ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fragShader.glsl ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad::glad
    glm::glm
    spdlog::spdlog_header_only
    ShaderProgram
    StbImage
)
