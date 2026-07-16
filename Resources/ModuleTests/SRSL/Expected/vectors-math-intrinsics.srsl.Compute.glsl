/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute

#version 450

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (set = 0, binding = 0) buffer StorageBuffer_outv {
	vec4 outv[];
};

void main() {
    vec3 a = vec3(1.0, 2.0, 3.0);
    vec3 b = vec3((-2.0), 0.5, 4.0);
    float d = dot(a, b);
    vec3 c = cross(a, b);
    vec3 n = normalize((a + b));
    float l0 = length(a);
    float l1 = length(b);
    float l2 = length(c);
    outv[0] = vec4(d, l0, l1, l2);
    outv[1] = vec4(c, 1.0);
    outv[2] = vec4(n, 1.0);
    outv[3] = vec4(clamp(d, (-10.0), 10.0), smoothstep(0.0, 1.0, 0.25), step(0.5, 0.25), 1.0);
}