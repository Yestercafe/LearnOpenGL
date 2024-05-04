//
// Created by ivan on 2024/5/4.
//

#include "GL.hpp"
#include <functional>
#include <spdlog/spdlog.h>

namespace lgl {

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GL::GL() : GL(800, 600) {}

GL::GL(int windowWidth, int windowHeight) : m_windowWidth_{windowWidth}, m_windowHeight_{windowHeight} {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_window_ = glfwCreateWindow(windowWidth, windowHeight, "Triangle", nullptr, nullptr);
    if (!m_window_) {
        spdlog::error("Failed to create GLFW window!");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_window_);
    glfwSetFramebufferSizeCallback(m_window_, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        spdlog::error("Failed to initialize GLAD!");
        return;
    }

    glEnable(GL_DEPTH_TEST);

    bValid = true;
}

bool GL::is_should_close() {
    return glfwWindowShouldClose(m_window_);
}

void GL::process_input() {
    if (glfwGetKey(m_window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window_, true);
}

void GL::swap_buffers() {
    glfwSwapBuffers(m_window_);
}

void GL::poll_events() {
    glfwPollEvents();
}

GL::~GL() {
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


}
