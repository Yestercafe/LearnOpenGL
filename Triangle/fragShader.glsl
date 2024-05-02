#version 330 core
in vec3 vertexColor;

void main() {
    gl_FragColor = vec4(vertexColor, 1.f);
}
