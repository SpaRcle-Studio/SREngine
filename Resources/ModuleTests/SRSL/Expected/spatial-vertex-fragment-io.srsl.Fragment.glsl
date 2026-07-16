/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Fragment
/// Shader type: Spatial

#version 450

layout (location = 0) in vec2 vUv;

layout (std140, binding = 1) uniform BLOCK {
	// (64 bytes) private
	mat4 MODEL_MATRIX;
	// (16 bytes) public
	vec4 TintColor;
};

layout (binding = 2) uniform sampler2D Albedo; // (sampler) public

vec4 COLOR;

vec4 COLOR_INDEX_0; /// emulate location 0
vec4 COLOR_INDEX_1; /// emulate location 1

void main() {
    vec3 albedo = texture(Albedo, vUv).rgb;
    COLOR = (vec4(albedo, 1.0) * TintColor);
    COLOR_INDEX_1 = vec4(gl_FragCoord.z);

    COLOR_INDEX_0 = COLOR;
}