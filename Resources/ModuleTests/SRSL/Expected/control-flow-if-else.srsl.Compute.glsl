/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute

#version 450

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

void main() {
    int a = 10;
    int b = 20;
    int c = 0;
    if ((a < b)) {
        c = 1;
    }
    else {
        c = 2;
    }
    if (((((a) == (10)) && ((b) == (20))) && ((c) == (1)))) {
        (c += 100);
    }
    else if ((((a) != (10)) || ((b) != (20)))) {
        (c += 200);
    }
    else {
        (c += 300);
    }
    bool ok = ((c > 0) && (!(c < 0)));
    ok = (ok || ((a) == (b)));
}