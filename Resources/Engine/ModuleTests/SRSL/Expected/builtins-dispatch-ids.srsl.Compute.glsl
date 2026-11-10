/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute
/// Shader macros:

#version 450

vec3 VERTEX; /// added by builtin
vec3 NORMAL; /// added by builtin
vec2 UV; /// added by builtin
vec4 TANGENT; /// added by builtin
layout (local_size_x = 4, local_size_y = 2, local_size_z = 1) in;

layout (set = 0, binding = 0) buffer StorageBuffer_outv {
	uvec4 outv[];
};

void main() {
    uvec3 gid = gl_GlobalInvocationID;
    uvec3 lid = gl_LocalInvocationID;
    uvec3 wid = gl_WorkGroupID;
    outv[0] = uvec4(gid, 1u);
    outv[1] = uvec4(lid, 1u);
    outv[2] = uvec4(wid, 1u);
    outv[3] = uvec4(gl_NumWorkGroups, 1u);
}