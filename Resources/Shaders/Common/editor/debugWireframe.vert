#version 450

layout (location = 0) in vec3 inPos;

layout (binding = 0) uniform MeshUBO {
    mat4 model;
} meshUBO;

layout (binding = 2) uniform ProjViewUBO {
    mat4 proj;
    mat4 view;
} sharedUBO;

#extension GL_ARB_separate_shader_objects : enable

void main() {
    gl_Position = sharedUBO.proj * sharedUBO.view * meshUBO.model * vec4(inPos, 1.0);
}