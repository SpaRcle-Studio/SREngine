/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Fragment
/// Shader type: Spatial

#version 450

vec4 COLOR;

vec4 COLOR_INDEX_0; /// emulate location 0

void main() {
    COLOR = vec4(((NORMAL * 0.5) + 0.5), 1.0);

    COLOR_INDEX_0 = COLOR;
}