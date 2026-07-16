/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute

#version 450

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (set = 0, binding = 0) buffer StorageBuffer_outData {
	int outData[];
};

void main() {
    int i = 0;
    int acc = 0;
    while ((i < 10)) {
        (acc += i);
        (i += 1);
    }
    int j = 10;
    while ((j > 0)) {
        (acc -= 1);
        (j -= 1);
    }
    outData[0] = i;
    outData[1] = acc;
}