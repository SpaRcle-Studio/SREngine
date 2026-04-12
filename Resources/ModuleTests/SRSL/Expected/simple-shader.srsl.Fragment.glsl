/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Fragment
/// Shader type: Spatial

#version 450

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

vec4 COLOR;

vec4 COLOR_INDEX_0; /// emulate location 0
vec4 COLOR_INDEX_1; /// emulate location 1
vec4 COLOR_INDEX_2; /// emulate location 2

void main() {
    vec3 viewDirectionWorld = (VIEW_MATRIX * vec4(VIEW_DIRECTION, 0)).xyz;
    vec3 normalWorld = (VIEW_MATRIX * vec4(NORMAL, 0.0)).xyz;
    COLOR = vec4(BubbleColor, Fresnel(viewDirectionWorld, normalWorld));
    COLOR_INDEX_1 = (vec4(gl_FragCoord.z) * max(0, (COLOR.a - 0.8)));
    COLOR_INDEX_2 = vec4(VERTEX, 1.0);

    COLOR_INDEX_0 = COLOR;
}