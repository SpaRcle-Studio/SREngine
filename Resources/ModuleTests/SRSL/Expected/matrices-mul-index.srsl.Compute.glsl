/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute

#version 450

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (std140, binding = 0) uniform BLOCK {
	// (64 bytes) private
	mat4 M;
};
layout (set = 0, binding = 1) buffer StorageBuffer_outv {
	vec4 outv[];
};

void main() {
    vec4 v = vec4(1.0, 2.0, 3.0, 1.0);
    vec4 r = (M * v);
    float m00 = M[0][0];
    float m13 = M[1][3];
    float m30 = M[3][0];
    outv[0] = r;
    outv[1] = vec4(m00, m13, m30, 1.0);
}