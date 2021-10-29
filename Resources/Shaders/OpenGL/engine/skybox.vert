#version 450

layout (location = 0) in vec3 aPos;

layout (location = 0) out vec3 UV;

uniform mat4 PVmat;

void main() {
    UV = aPos;
    gl_Position = (PVmat * vec4(aPos, 1.0)).xyww;
}