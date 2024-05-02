//
// Created by ivan on 2024/5/2.
//

#ifndef LEARNOPENGL_SHADER_HPP
#define LEARNOPENGL_SHADER_HPP

#include <string>
#include <map>
#include <spdlog/spdlog.h>

namespace lgl {

class Shader {
public:
    enum class Type {
        Vertex,
        Fragment,
        Program,
    };

    Shader();
    ~Shader();
    int add(Type type, const std::string& path);
    int link();
    int use();

    int get_attribute_location(const char* name);

private:
    static int checkout_compile_error_(unsigned int shader, Type type);

    std::map<Type, unsigned int> m_shaders_;
    unsigned int m_program_ = 0;
};

}

#endif //LEARNOPENGL_SHADER_HPP
