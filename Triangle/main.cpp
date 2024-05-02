#include <vector>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <spdlog/spdlog.h>
#include <shader.hpp>

constexpr unsigned int WindowWidth = 800;
constexpr unsigned int WindowHeight = 600;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void process_input(GLFWwindow *window);

int main() {
    spdlog::set_level(spdlog::level::debug);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, "Triangle", nullptr, nullptr);
    if (!window) {
        spdlog::error("Failed to create GLFW window!");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        spdlog::error("Failed to initialize GLAD!");
        return -1;
    }

    lgl::Shader shader;
    shader.add(lgl::Shader::Type::Vertex, "./vertexShader.glsl");
    shader.add(lgl::Shader::Type::Fragment, "./fragShader.glsl");
    shader.link();

    std::vector<GLfloat> vertices {
        0.5f, -0.5f, 0.0f, 1.f, 0.f, 0.f,
        -0.5f, -0.5f, 0.0f, 0.f, 1.f, 0.f,
        0.0f, 0.5f, 0.0f, 0.f, 0.f, 1.f,
    };

    unsigned int vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(*vertices.data()), vertices.data(), GL_STATIC_DRAW);

    auto posLoc = shader.get_attribute_location("aPos");
    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(*vertices.data()), (void *) 0);
    glEnableVertexAttribArray(posLoc);
    auto colorLoc = shader.get_attribute_location("aColor");
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(*vertices.data()), (void *) (3 * sizeof(*vertices.data())));
    glEnableVertexAttribArray(colorLoc);

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void process_input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
