/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute

#version 450

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (set = 0, binding = 0) buffer StorageBuffer_bits {
	uint bits[];
};

void main() {
    uint a = 0x0Fu;
    uint b = 0xF0u;
    uint andv = (a & b);
    uint orv = (a | b);
    uint xorv = (a ^ b);
    uint notv = (~a);
    uint shl = (a << 4u);
    uint shr = (b >> 2u);
    bits[0] = andv;
    bits[1] = orv;
    bits[2] = xorv;
    bits[3] = notv;
    bits[4] = shl;
    bits[5] = shr;
}