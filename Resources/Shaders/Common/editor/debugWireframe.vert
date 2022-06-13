#version 450

layout (location = 0) in vec3 inPos;

layout (binding = 0) uniform WireframeUBO {
    mat4 model;
    vec4 color;
} wireframeUBO;

layout (binding = 1) uniform ProjViewUBO {
    mat4 proj;
    mat4 view;
};

#extension GL_ARB_separate_shader_objects : enable

void main() {
    gl_Position = proj * view * wireframeUBO.model * vec4(inPos, 1.0);
}