/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute

#version 450

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

struct Item {
    vec4 color;
    vec3 pos;
    float weight;
};

layout (set = 0, binding = 0) buffer StorageBuffer_items {
	uint itemsCount;
	Item items[];
};
layout (set = 0, binding = 1) buffer StorageBuffer_outv {
	vec4 outv[];
};

vec4 Accumulate(uint idx) {
    Item it = items[idx];
    float w = max(0.0, it.weight);
    return ((it.color * w) + (vec4(it.pos, 1.0) * (1.0 - w)));

}

void main() {
    uint idx0 = 0u;
    uint idx1 = min(1u, itemsCount);
    vec4 a = Accumulate(idx0);
    vec4 b = Accumulate(idx1);
    outv[0] = a;
    outv[1] = b;
    outv[2] = mix(a, b, 0.5);
}