#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D uTexture1;
uniform sampler2D uTexture2;

void main() {
    FragColor = mix(texture(uTexture1, texCoord), texture(uTexture2, texCoord), 0.2);
}
