/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute

#version 450

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (set = 0, binding = 0) buffer StorageBuffer_outv {
	float outv[];
};

void main() {
    float a = 0.0;
    float b = 1.0;
    float c = (-1.0);
    float s0 = sign(c);
    float s1 = sign(b);
    float p = pow(2.0, 10.0);
    float e = exp2(5.0);
    float l = log2(32.0);
    outv[0] = s0;
    outv[1] = s1;
    outv[2] = p;
    outv[3] = e;
    outv[4] = l;
    outv[5] = mix(a, b, 0.25);
}