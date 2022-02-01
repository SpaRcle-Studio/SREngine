#version 450

layout (location = 0) in vec3 aPos;

layout (location = 0) out vec3 UV;

uniform mat4 PVmat;

void main() {
    UV = aPos;
    vec4 vPos = vec4(-aPos.x, aPos.y, aPos.z, 1.0);
    gl_Position = (PVmat * vPos).xyww;
}