//
// Created by ivan on 2024/5/4.
//

#ifndef GL_HPP
#define GL_HPP

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace lgl {

class GL {
public:
    GL();
    GL(int windowWidth, int windowHeight);

    GLFWwindow *get_window() { return m_window_; }
    int get_window_width() const { return m_windowWidth_; }
    int get_window_height() const { return m_windowHeight_; }

    bool is_should_close();
    void process_input();
    void swap_buffers();
    void poll_events();

    ~GL();

private:
    bool bValid = false;
    GLFWwindow *m_window_ = nullptr;
    int m_windowWidth_{}, m_windowHeight_{};
};

}

#endif //GL_HPP
