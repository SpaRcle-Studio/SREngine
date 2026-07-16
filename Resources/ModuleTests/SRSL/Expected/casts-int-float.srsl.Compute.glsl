/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute

#version 450

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (std140, binding = 0) uniform BLOCK {
	// (8 bytes) private
	vec2 resolution;
};
layout (set = 0, binding = 1) buffer StorageBuffer_outData {
	float outData[];
};

void main() {
    int rx = int(resolution.x);
    int ry = int(resolution.y);
    float fx = float(rx);
    float fy = float(ry);
    outData[0] = (fx / max(1.0, resolution.x));
    outData[1] = (fy / max(1.0, resolution.y));
    outData[2] = float(int((fx + fy)));
}