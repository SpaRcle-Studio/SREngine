/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute

#version 450

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (set = 0, binding = 0) buffer StorageBuffer_outv {
	int outv[];
};

bool IsPositive(int x) {
    return (x > 0);

}

bool IsEven(int x) {
    return (((x & 1)) == (0));

}

void main() {
    int a = 2;
    int b = (-3);
    bool p = (IsPositive(a) && IsEven(a));
    bool q = (IsPositive(b) && IsEven(b));
    bool r = (IsPositive(b) || IsEven(a));
    outv[0] = int(p);
    outv[1] = int(q);
    outv[2] = int(r);
}