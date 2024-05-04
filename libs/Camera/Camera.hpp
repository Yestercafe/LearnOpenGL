//
// Created by ivan on 2024/5/4.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL.hpp>

namespace lgl {

class Camera {
public:
    Camera(GL *gl);
    void context();

    glm::mat4 view() const;

    void inc_yaw(double angle);
    void inc_pitch(double angle);

    ~Camera();

private:
    GL *gl = nullptr;

    glm::vec3 m_cameraPos_;
    glm::vec3 m_cameraUp_;
    glm::vec3 m_lookingAt_;
    glm::vec3 m_rotateAxis_;

    double m_yaw_ = 0.;
    double m_pitch_ = 0.;
};

}

#endif //CAMERA_HPP
