#version 450

layout (location = 0) in vec2 inUV;
layout (location = 0) out vec4 outColor;

layout (binding = 0) uniform PostProcessingUBO {
    float gamma;
    float saturation;
} ubo;

layout (binding = 1) uniform sampler2D GeometryMap;

void main() {
    //vec4 color = texture(GeometryMap, inUV);
    //if (color.a == 0)
    //    outColor = vec4(1, 0, 0, 1);
    //else
    outColor = vec4(0, 1, 0, 1);
}
