#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 PVmat;

void main() {
    TexCoords = aPos;
    gl_Position = (PVmat * vec4(aPos, 1.0)).xyww;
}