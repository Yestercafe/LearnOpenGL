//
// Created by ivan on 2024/5/2.
//

#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <glad/glad.h>

namespace lgl {

Shader::Shader() {

}

Shader::~Shader() {

}

int Shader::add(Type type, const std::string& path) {
    if (m_shaders_.contains(type)) {
        spdlog::warn("This type of shader has been bound!");
        return -1;
    }
    if (Type::Program == type) {
        spdlog::warn("Type::Program is not a valid type of shader!");
        return -2;
    }

    std::ifstream reader(path);
    std::string shaderSource;
    try {
        std::stringstream ss;
        ss << reader.rdbuf();
        shaderSource = ss.str();
    } catch (std::exception& e){
        spdlog::error("{}", e.what());
    }

    const char* shaderSourceCStr = shaderSource.c_str();
    spdlog::debug("{}", shaderSource);
    unsigned int shader = 0;
    if (Type::Vertex == type) {
        shader = glCreateShader(GL_VERTEX_SHADER);
    } else if (Type::Fragment == type) {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    }
    glShaderSource(shader, 1, &shaderSourceCStr, nullptr);

    glCompileShader(shader);
    auto ret = checkout_compile_error_(shader, type);
    if (ret) {
        return ret;
    }

    if (0 == m_program_) {
        m_program_ = glCreateProgram();
    }
    glAttachShader(m_program_, shader);

    m_shaders_[type] = shader;
    glDeleteShader(shader);

    return 0;
}

int Shader::link() {
    if (0 == m_program_) {
        return -1;
    }
    glLinkProgram(m_program_);
    return checkout_compile_error_(m_program_, Type::Program);
}

int Shader::use() {
    if (0 == m_program_) {
        return -1;
    }
    glUseProgram(m_program_);
    return 0;
}

int Shader::get_attribute_location(const char *name) {
    return glGetAttribLocation(m_program_, name);
}


int Shader::checkout_compile_error_(const unsigned int shader, const Type type) {
    int succ = 0;
    char infoLog[1024]{};
    if (Type::Program == type) {
        glGetProgramiv(shader, GL_LINK_STATUS, &succ);
        if (!succ) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
        }
    } else {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &succ);
        if (!succ) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        }
    }
    if (!succ) {
        spdlog::error("Shader program error: {}", infoLog);
        return -100;
    }
    return 0;
}

}