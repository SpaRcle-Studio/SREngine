/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute

#version 450

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (set = 0, binding = 0) buffer StorageBuffer_dst {
	uint dst[];
};

void main() {
    uint sum = 0u;
    uint prod = 1u;
    for (uint i = 0u; (i < 16u); (i += 1u)) {
        if ((((i & 1u)) == (0u))) {
            continue;
        }
        (sum += i);
        (prod *= (i + 1u));
        if ((i > 11u)) {
            break;
        }
    }
    dst[0] = sum;
    dst[1] = prod;
}