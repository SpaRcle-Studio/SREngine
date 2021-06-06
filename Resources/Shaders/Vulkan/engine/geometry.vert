#version 450

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inUV;
layout (location = 2) in vec3 inNorm;
layout (location = 3) in vec3 inTang;

layout (location = 0) out vec3 outUV;

layout (binding = 0) uniform ProjViewUBO {
    mat4 proj;
    mat4 view;
} sharedUBO;

layout (binding = 1) uniform MeshUBO {
    mat4 model;
} meshUBO;

#extension GL_ARB_separate_shader_objects : enable

void main() {
    outUV = vec3(inUV, 0);

    mat4 view = mat4(0.981977, 0.084292, -0.169163, 0.000000, 0.000000, 0.895039, 0.445988, 0.000000, 0.189001, -0.437950, 0.878908, 0.000000, 0.436443, -0.294155, -5.903755, 1.000000);
    mat4 proj = mat4(1.357995, 0.000000, 0.000000, 0.000000, 0.000000, 2.414213, 0.000000, 0.000000, 0.000000, 0.000000, -1.000025, -1.000000, 0.000000, 0.000000, -0.200003, 0.000000);

    gl_Position = proj * view * vec4(inPos, 1.0);
}