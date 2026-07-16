/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute

#version 450

const float LUT2[2][3] = { 
        { 
                0.25,
                0.5,
                0.75
            },
        { 
                1.25,
                1.5,
                1.75
            }
    };

const int LUT1[8] = { 
        0,
        1,
        1,
        2,
        3,
        5,
        8,
        13
    };

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (set = 0, binding = 0) buffer StorageBuffer_outv {
	float outv[];
};

float GetLut2(uint x, uint y) {
    return LUT2[x][y];

}

void main() {
    int a = (LUT1[0] + LUT1[7]);
    int b = (LUT1[3] * LUT1[4]);
    float x = GetLut2(0u, 1u);
    float y = GetLut2(1u, 2u);
    outv[0] = float(a);
    outv[1] = float(b);
    outv[2] = (x + y);
}