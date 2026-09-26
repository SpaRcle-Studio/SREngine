/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Fragment
/// Shader type: Line
/// Shader macros:

#version 450

layout (location = 0) in vec4 lineColor;
vec3 VERTEX; /// added by builtin
vec3 NORMAL; /// added by builtin
vec2 UV; /// added by builtin
vec4 TANGENT; /// added by builtin

layout (set = 0, binding = 1) buffer StorageBuffer_lines {
	vec3 points[];
};

vec4 COLOR;

vec4 COLOR_INDEX_0; /// emulate location 0

void main() {
    COLOR = lineColor;

    COLOR_INDEX_0 = COLOR;
}