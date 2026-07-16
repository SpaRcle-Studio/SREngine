/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Vertex
/// Shader type: Line

#version 450

vec3 VERTEX; /// added by builtin
vec3 NORMAL; /// added by builtin
vec2 UV; /// added by builtin
layout (location = 0) out vec4 lineColor; /// added by shared

layout (std140, binding = 0) uniform SHARED {
	// (64 bytes) private
	mat4 PROJECTION_MATRIX;
	// (64 bytes) private
	mat4 VIEW_MATRIX;
};
layout (set = 0, binding = 1) buffer StorageBuffer_lines {
	vec3 points[];
};

void main() {
    vec4 OUT_POSITION;
    int VERTEX_INDEX = gl_VertexIndex;

    uint idx = ((gl_InstanceIndex * 2u) + uint(VERTEX_INDEX));
    vec3 p = points[idx];
    lineColor = vec4(abs(p), 1.0);
    OUT_POSITION = ((PROJECTION_MATRIX * VIEW_MATRIX) * vec4(p, 1.0));

    gl_Position = OUT_POSITION;
}