/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Fragment
/// Shader type: Line

#version 450

layout (location = 0) in vec4 lineColor;

layout (set = 0, binding = 1) buffer StorageBuffer_lines {
	vec3 points[];
};

vec4 COLOR;

vec4 COLOR_INDEX_0; /// emulate location 0

void main() {
    COLOR = lineColor;

    COLOR_INDEX_0 = COLOR;
}