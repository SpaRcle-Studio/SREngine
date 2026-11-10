/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute
/// Shader macros:

#version 450

vec3 VERTEX; /// added by builtin
vec3 NORMAL; /// added by builtin
vec2 UV; /// added by builtin
vec4 TANGENT; /// added by builtin
layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (set = 0, binding = 0) buffer StorageBuffer_outv {
	int outv[];
};

int ClampInt(int v, int lo, int hi) {
    if ((v < lo)) {
        return lo;

    }
    if ((v > hi)) {
        return hi;

    }
    return v;

}

int Fib(int n) {
    if ((n <= 1)) {
        return n;

    }
    return (Fib((n - 1)) + Fib((n - 2)));

}

void main() {
    int a = ClampInt((-10), 0, 5);
    int b = ClampInt(123, 0, 5);
    int c = ClampInt(3, 0, 5);
    int f = Fib(7);
    outv[0] = a;
    outv[1] = b;
    outv[2] = c;
    outv[3] = f;
}