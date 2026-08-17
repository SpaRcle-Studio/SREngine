/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Vertex
/// Shader type: Skybox

#version 450

layout (location = 0) out vec3 VERTEX; /// added by builtin
vec3 NORMAL; /// added by builtin
vec2 UV; /// added by builtin

layout (std140, binding = 0) uniform SHARED {
	// (64 bytes) private
	mat4 PROJECTION_MATRIX;
	// (64 bytes) private
	mat4 VIEW_NO_TRANSLATE_MATRIX;
	// (12 bytes) private
	vec3 DIRECTIONAL_LIGHT_DIRECTION;
	// (12 bytes) private
	vec3 GROUND_COLOR;
	// (12 bytes) private
	vec3 SKY_COLOR;
	// (12 bytes) private
	vec3 SUN_COLOR;
	// (4 bytes) private
	float SUN_INTENSITY;
};

void main() {
    vec4 OUT_POSITION;

    OUT_POSITION = ((PROJECTION_MATRIX * VIEW_NO_TRANSLATE_MATRIX) * vec4(VERTEX, 1.0)).xyww;

    gl_Position = OUT_POSITION;
}