//
// Created by ivan on 2024/5/4.
//

#include "Camera.hpp"
#include <utility>
#include <cmath>
#include <spdlog/spdlog.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace lgl {

enum class MouseButton {
    None,
    Left,
    Right,
};

static Camera* gCamera = nullptr;
static MouseButton gMouseButton = MouseButton::None;
static std::pair gLastCursorPosOpt{false, std::make_pair(0., 0.)};

static void cursor_pos_callback(GLFWwindow *widow, double xpos, double ypos);
static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

Camera::Camera(GL *gl) : m_cameraPos_(0.f, 0.f, 3.f), m_cameraUp_(0.f, 1.f, 0.f), m_lookingAt_(0.f, 0.f, 0.f), m_rotateAxis_(0.f, 1.f, 0.f){
    if (!gl) {
        spdlog::error("GL in Camera is null!");
        assert(false);
    }

    glfwSetCursorPosCallback(gl->get_window(), cursor_pos_callback);
    glfwSetMouseButtonCallback(gl->get_window(), mouse_button_callback);

    context();
}

void Camera::context() {
    gCamera = this;
}

glm::mat4 Camera::view() const {
    return glm::lookAt(m_cameraPos_, m_lookingAt_, m_cameraUp_);
}

static glm::vec3 from_yaw_pitch(double yaw, double pitch) {
    yaw = float(glm::radians(yaw));
    pitch = float(glm::radians(pitch));
    return {
        std::cos(pitch) * std::sin(yaw),
        std::sin(pitch),
        std::cos(pitch) * std::cos(yaw)
    };
}

void Camera::inc_yaw(double angle) {
    m_yaw_ += angle;

    auto dist = glm::length(m_cameraPos_ - m_lookingAt_);
    m_cameraPos_ = dist * from_yaw_pitch(m_yaw_, m_pitch_) + m_lookingAt_;
    m_cameraUp_ = glm::rotate(glm::mat4(1.f), glm::radians(float(angle)), m_rotateAxis_) * glm::vec4(m_cameraUp_, 1.f);

    spdlog::debug("yaw: {}", m_yaw_);
}

void Camera::inc_pitch(double angle) {
    m_pitch_ += angle;
    // FIXME:
    m_pitch_ = std::clamp(m_pitch_, -89., 89.);

    auto dist = glm::length(m_cameraPos_ - m_lookingAt_);

    auto frontDirection = glm::normalize(m_lookingAt_ - m_cameraPos_);
    auto upDirection = glm::normalize(m_cameraUp_);
    auto rightDirection = glm::normalize(glm::cross(frontDirection, upDirection));
    spdlog::debug("1 angle: {} {} {}", glm::angle(frontDirection, upDirection), glm::angle(upDirection, rightDirection), glm::angle(frontDirection, rightDirection));

    m_cameraPos_ = dist * from_yaw_pitch(m_yaw_, m_pitch_) + m_lookingAt_;
    frontDirection = glm::normalize(m_lookingAt_ - m_cameraPos_);
    m_cameraUp_ = glm::cross(rightDirection, frontDirection);

    frontDirection = glm::normalize(m_lookingAt_ - m_cameraPos_);
    upDirection = glm::normalize(m_cameraUp_);
    spdlog::debug("angle: {} {} {}", glm::angle(frontDirection, upDirection), glm::angle(upDirection, rightDirection), glm::angle(frontDirection, rightDirection));

    spdlog::debug("pitch: {}", m_pitch_);
}

Camera::~Camera() {

}

void cursor_pos_callback(GLFWwindow *widow, double xpos, double ypos) {
    if (!gCamera) return;

    std::pair<double, double> delta;
    if (MouseButton::None != gMouseButton) {
        if (!gLastCursorPosOpt.first) {
            gLastCursorPosOpt.first = true;
            gLastCursorPosOpt.second = {xpos, ypos};
            return;
        }
        delta.first = xpos - gLastCursorPosOpt.second.first;
        delta.second = ypos - gLastCursorPosOpt.second.second;
        gLastCursorPosOpt.second = {xpos, ypos};
    } else {
        gLastCursorPosOpt.first = false;
        return;
    }

    if (MouseButton::Left == gMouseButton) {
        gCamera->inc_yaw(-delta.first);
        gCamera->inc_pitch(delta.second);
    } else if (MouseButton::Right == gMouseButton) {
        spdlog::info("right {} {}", delta.first, delta.second);
    }
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (!gCamera) return;
    if (GLFW_MOUSE_BUTTON_LEFT == button && GLFW_PRESS == action) {
        gMouseButton = MouseButton::Left;
    }
    if (GLFW_MOUSE_BUTTON_RIGHT == button && GLFW_PRESS == action) {
        gMouseButton = MouseButton::Right;
    }
    if (GLFW_RELEASE == action) {
        gMouseButton = MouseButton::None;
    }
}

}
