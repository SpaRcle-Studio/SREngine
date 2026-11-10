/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute
/// Shader macros:

#version 450

vec3 VERTEX; /// added by builtin
vec3 NORMAL; /// added by builtin
vec2 UV; /// added by builtin
vec4 TANGENT; /// added by builtin
layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (set = 0, binding = 0) buffer StorageBuffer_outv {
	int outv[];
};

void main() {
    int a = 123;
    int b = 10;
    int q = (a / b);
    int r = (a % b);
    int c = (-123);
    int q2 = (c / b);
    int r2 = (c % b);
    outv[0] = q;
    outv[1] = r;
    outv[2] = q2;
    outv[3] = r2;
}