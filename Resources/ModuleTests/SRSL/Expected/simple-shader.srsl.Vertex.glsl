/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Vertex
/// Shader type: Spatial

#version 450

layout (location = 0) out vec3 VERTEX; /// added by builtin
layout (location = 1) out vec3 NORMAL; /// added by builtin
vec2 UV; /// added by builtin

layout (std140, binding = 0) uniform SHARED {
	// (64 bytes) private
	mat4 PROJECTION_MATRIX;
	// (64 bytes) private
	mat4 VIEW_MATRIX;
	// (12 bytes) private
	vec3 VIEW_DIRECTION;
	// (4 bytes) private
	float TIME;
};
layout (std140, binding = 1) uniform BLOCK {
	// (64 bytes) private
	mat4 MODEL_MATRIX;
	// (12 bytes) public
	vec3 BubbleColor;
	// (4 bytes) public
	float NoiseSampleSize;
	// (4 bytes) public
	float AnimationSpeed;
	// (4 bytes) public
	float HeightMultiplier;
};

layout (binding = 2) uniform sampler2D NoiseTex; // (sampler) public

void main() {
    vec4 OUT_POSITION;

    float height = texture(NoiseTex, ((VERTEX.xz * (NoiseSampleSize / 100.0)) + (vec2(TIME) * (AnimationSpeed / 1000.0)))).r;
    (VERTEX += ((VERTEX * height) * HeightMultiplier));
    VERTEX = (MODEL_MATRIX * vec4(VERTEX, 1.0)).xyz;
    OUT_POSITION = ((PROJECTION_MATRIX * VIEW_MATRIX) * vec4(VERTEX, 1.0));

    gl_Position = OUT_POSITION;
}