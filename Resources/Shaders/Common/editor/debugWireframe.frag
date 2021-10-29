#version 450

#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) out vec4 outColor;

layout (location = 0) in vec2 TexCoord;

layout (binding = 1) uniform ColorRGB {
    vec3 color;
} colorRGB;

void main() {
    outColor = vec4(colorRGB, 1.f);
}