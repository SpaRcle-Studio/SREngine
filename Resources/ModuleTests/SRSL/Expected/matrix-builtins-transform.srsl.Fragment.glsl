/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Fragment
/// Shader type: Spatial
/// Shader macros:

#version 450

vec3 VERTEX; /// added by builtin
vec3 NORMAL; /// added by builtin
vec2 UV; /// added by builtin
vec4 TANGENT; /// added by builtin

vec4 COLOR;

vec4 COLOR_INDEX_0; /// emulate location 0

void main() {
    COLOR = vec4(((NORMAL * 0.5) + 0.5), 1.0);

    COLOR_INDEX_0 = COLOR;
}