/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute

#version 450

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (set = 0, binding = 0) buffer StorageBuffer_outv {
	int outv[];
};

void main() {
    int[4] a = { 
        1,
        2,
        3,
        4
    };
    int[2][2] b = { 
        { 
                10,
                11
            },
        { 
                20,
                21
            }
    };
    float[2][3] c = { 
        { 
                0.1,
                0.2,
                0.3
            },
        { 
                1.1,
                1.2,
                1.3
            }
    };
    int idx = ((a[0] + a[3]) - 3);
    int v0 = a[idx];
    int v1 = (b[0][1] + b[1][0]);
    int v2 = int((c[1][2] * 10.0));
    outv[0] = v0;
    outv[1] = v1;
    outv[2] = v2;
}