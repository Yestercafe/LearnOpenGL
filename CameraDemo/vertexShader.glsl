#version 330 core
in vec3 aPos;
in vec3 aColor;
in vec2 aTexCoord;

out vec3 vertexColor;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.f);
    vertexColor = aColor;
    texCoord = aTexCoord;
}
