#version 450

layout (location = 0) in vec2 inUV;
layout (location = 0) out vec4 outColor;

layout (binding = 0) uniform PostProcessingUBO {
    float gamma;
    float saturation;
} ubo;

layout (binding = 1) uniform sampler2D GeometryMap;
layout (binding = 2) uniform sampler2D SkyboxMap;

void main() {
    outColor = vec4(texture(GeometryMap, inUV).rgb + texture(SkyboxMap, inUV).rgb, 1.0);
}
