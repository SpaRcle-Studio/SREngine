/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Vertex
/// Shader type: Spatial

#version 450

vec3 VERTEX; /// added by builtin
vec3 NORMAL; /// added by builtin
vec2 UV; /// added by builtin
layout (location = 0) out vec2 vUv; /// added by shared

layout (std140, binding = 0) uniform SHARED {
	// (64 bytes) private
	mat4 PROJECTION_MATRIX;
	// (64 bytes) private
	mat4 VIEW_MATRIX;
};
layout (std140, binding = 1) uniform BLOCK {
	// (64 bytes) private
	mat4 MODEL_MATRIX;
	// (16 bytes) public
	vec4 TintColor;
};

void main() {
    vec4 OUT_POSITION;

    vUv = UV;
    vec3 p = VERTEX;
    (p += (NORMAL * 0.01));
    VERTEX = (MODEL_MATRIX * vec4(p, 1.0)).xyz;
    OUT_POSITION = ((PROJECTION_MATRIX * VIEW_MATRIX) * vec4(VERTEX, 1.0));

    gl_Position = OUT_POSITION;
}