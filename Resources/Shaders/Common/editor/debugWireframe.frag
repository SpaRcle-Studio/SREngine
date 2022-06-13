#version 450

#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) out vec4 outColor;

layout (binding = 0) uniform WireframeUBO {
    mat4 model;
    vec4 color;
} wireframeUBO;

void main() {
    outColor = wireframeUBO.color;
}
