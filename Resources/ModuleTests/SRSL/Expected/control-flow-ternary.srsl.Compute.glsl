/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute

#version 450

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (std140, binding = 0) uniform BLOCK {
	// (4 bytes) private
	int threshold;
};
layout (set = 0, binding = 1) buffer StorageBuffer_outBuf {
	int outBuf[];
};

int SelectValue(int x, int y) {
    return ((x > y) ? x : y);

}

void main() {
    int x = 5;
    int y = 7;
    int m = SelectValue(x, y);
    int r0 = ((m >= threshold) ? (m + 1) : (m - 1));
    int r1 = (((x + y) > 0) ? (x + y) : (-(x + y)));
    outBuf[0] = r0;
    outBuf[1] = r1;
}