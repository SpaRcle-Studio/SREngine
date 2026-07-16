/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute

#version 450

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (set = 0, binding = 0) buffer StorageBuffer_src {
	float src[];
};
layout (set = 0, binding = 1) buffer StorageBuffer_dst {
	float dst[];
};

void main() {
    float a = src[0];
    float b = src[1];
    float c = src[2];
    dst[0] = (a + b);
    dst[1] = (b * c);
    dst[2] = max(a, c);
    dst[3] = min(a, c);
}