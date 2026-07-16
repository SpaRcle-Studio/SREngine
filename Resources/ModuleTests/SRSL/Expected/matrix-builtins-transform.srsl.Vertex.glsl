/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Vertex
/// Shader type: Spatial

#version 450

vec3 VERTEX; /// added by builtin
layout (location = 0) out vec3 NORMAL; /// added by builtin
vec2 UV; /// added by builtin

layout (std140, binding = 0) uniform SHARED {
	// (64 bytes) private
	mat4 PROJECTION_MATRIX;
	// (64 bytes) private
	mat4 VIEW_MATRIX;
};
layout (std140, binding = 1) uniform BLOCK {
	// (64 bytes) private
	mat4 MODEL_MATRIX;
	// (4 bytes) public
	float Scale;
};

void main() {
    vec4 OUT_POSITION;

    vec3 p = (VERTEX * Scale);
    vec4 world = (MODEL_MATRIX * vec4(p, 1.0));
    vec4 view = (VIEW_MATRIX * world);
    OUT_POSITION = (PROJECTION_MATRIX * view);
    VERTEX = world.xyz;

    gl_Position = OUT_POSITION;
}