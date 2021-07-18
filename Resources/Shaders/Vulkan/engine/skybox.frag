#version 450

layout (location = 0) in vec3 UV;

layout (binding = 1) uniform samplerCube cubeMapTexture;

layout (location = 0) out vec4 outColor;

void main() {
    outColor = texture(cubeMapTexture, UV);
    //outColor = vec4(UV, 1);
}
