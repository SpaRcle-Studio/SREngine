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

layout (set = 0, binding = 0) buffer StorageBuffer_vout {
	vec4 vout[];
};

void main() {
    vec2 a = vec2(1.0, 2.0);
    vec3 b = vec3(a, 3.0);
    vec4 c = vec4(b, 4.0);
    vec3 xyz = c.xyz;
    vec2 yx = a.yx;
    vec4 zzzz = vec4(c.z);
    vout[0] = c;
    vout[1] = vec4(xyz, 1.0);
    vout[2] = vec4(yx, yx);
    vout[3] = zzzz;
}