#version 450

layout (location = 0) in vec3 inPos;

layout (location = 0) out vec4 rgbaColor;

layout (binding = 0) uniform WireframeUBO {
    mat4 model;
    vec4 color;
} wireframeUBO;

layout (binding = 2) uniform ProjViewUBO {
    mat4 proj;
    mat4 view;
} sharedUBO;

#extension GL_ARB_separate_shader_objects : enable

void main() {
    rgbaColor = wireframeUBO.color;
    gl_Position = sharedUBO.proj * sharedUBO.view * meshUBO.model * vec4(inPos, 1.0);
}