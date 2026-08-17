/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Fragment
/// Shader type: Skybox

#version 450

layout (binding = 1) uniform samplerCube SKYBOX_DIFFUSE; // (sampler) private

vec4 COLOR;

vec4 COLOR_INDEX_0; /// emulate location 0
vec4 COLOR_INDEX_1; /// emulate location 1
vec4 COLOR_INDEX_2; /// emulate location 2
vec4 COLOR_INDEX_3; /// emulate location 3

void main() {
    COLOR = texture(SKYBOX_DIFFUSE, VERTEX);
    COLOR_INDEX_1 = vec4(0.0);
    COLOR_INDEX_2 = vec4(0.0);
    COLOR_INDEX_3 = vec4(0.0);

    COLOR_INDEX_0 = COLOR;
}