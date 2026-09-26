/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute
/// Shader macros:

#version 450

vec3 VERTEX; /// added by builtin
vec3 NORMAL; /// added by builtin
vec2 UV; /// added by builtin
vec4 TANGENT; /// added by builtin
layout (local_size_x = 64, local_size_y = 1, local_size_z = 1) in;

shared float[64] shData;
layout (std140, binding = 0) uniform BLOCK {
	// (4 bytes) private
	uint elementCount;
};
layout (set = 0, binding = 1) buffer StorageBuffer_src {
	float src[];
};
layout (set = 0, binding = 2) buffer StorageBuffer_dst {
	float dst[];
};

void main() {
    uint gid = gl_GlobalInvocationID.x;
    uint tid = gl_LocalInvocationIndex;
    shData[tid] = ((gid < elementCount) ? src[gid] : 0.0);
    barrier();
    for (uint s = 32u; (s > 0u); (s >>= 1u)) {
        if ((tid < s)) {
            (shData[tid] += shData[(tid + s)]);
        }
        barrier();
    }
    if (((tid) == (0u))) {
        dst[gl_WorkGroupID.x] = shData[0];
    }
}