/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute

#version 450

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (std140, binding = 0) uniform BLOCK {
	// (8 bytes) private
	vec2 resolution;
};
layout (set = 0, binding = 1) buffer StorageBuffer_outv {
	vec4 outv[];
};

layout (binding = 2) uniform sampler2D inputTex; // (sampler) private

void main() {
    ivec2 gid = ivec2(gl_GlobalInvocationID.xy);
    vec2 uv = ((vec2(gid) + 0.5) / max(vec2(1.0), resolution));
    vec3 rgb = texture(inputTex, uv).rgb;
    float lum = max(dot(rgb, vec3(0.2126, 0.7152, 0.0722)), 1e-6);
    outv[0] = vec4(rgb, 1.0);
    outv[1] = vec4(lum, lum, lum, 1.0);
}