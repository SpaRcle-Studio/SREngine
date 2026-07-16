/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute

#version 450

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (set = 0, binding = 0) buffer StorageBuffer_nums {
	uint nums[];
};

void main() {
    float a = 1e-6;
    float b = (1e + 3);
    float c = (-2.5e-2);
    int i0 = 0;
    int i1 = (-1);
    int i2 = 0x7FFFFFFF;
    uint u0 = 0u;
    uint u1 = 1u;
    uint u2 = 0xFFFFFFFFu;
    nums[0] = uint((a * 1000000.0));
    nums[1] = uint(b);
    nums[2] = uint((abs(c) * 1000.0));
    nums[3] = uint(i0);
    nums[4] = uint(i1);
    nums[5] = uint(i2);
    nums[6] = u0;
    nums[7] = u1;
    nums[8] = u2;
}