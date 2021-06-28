#version 450

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inUV;
layout (location = 2) in vec3 inNorm;
layout (location = 3) in vec3 inTang;

layout (binding = 0) uniform MeshUBO {
    mat4 model;
} meshUBO;

layout (binding = 1) uniform ProjViewUBO {
    mat4 proj;
    mat4 view;
} sharedUBO;

layout (location = 0) out vec3 outPos;

#extension GL_ARB_separate_shader_objects : enable

void main() {
    outPos = inNorm;
    gl_Position = sharedUBO.proj * sharedUBO.view * meshUBO.model * vec4(inPos, 1.0);
}