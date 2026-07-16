/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute

#version 450

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (set = 0, binding = 0) buffer StorageBuffer_outv {
	int outv[];
};

int F(int x) {
    return ((x * 2) + 1);

}

void main() {
    int a = 2;
    int b = 3;
    int c = 4;
    int r0 = (a + (b * c));
    int r1 = ((a + b) * c);
    int r2 = (F(a) + (F(b) * F(c)));
    int r3 = ((a << 1) + ((b >> 1) * (c & 3)));
    int r4 = (((a) == (2)) ? (b + c) : (b - c));
    outv[0] = r0;
    outv[1] = r1;
    outv[2] = r2;
    outv[3] = r3;
    outv[4] = r4;
}