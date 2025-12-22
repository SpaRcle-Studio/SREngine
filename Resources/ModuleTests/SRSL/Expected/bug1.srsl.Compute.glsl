/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Compute
/// Shader type: Compute

#version 450

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (std140, binding = 0) uniform SHARED {
	// (256 bytes) private
	mat4 CASCADE_LIGHT_SPACE_MATRICES[4];
};

void main() {
    (CASCADE_LIGHT_SPACE_MATRICES[cascadeIndex] * vec4());
    (CASCADE_LIGHT_SPACE_MATRICES[cascadeIndex] * vec4(1));
    (CASCADE_LIGHT_SPACE_MATRICES[cascadeIndex] * vec4(1, 2, 3));
    (CASCADE_LIGHT_SPACE_MATRICES[(cascadeIndex + 1)] * vec4());
    (CASCADE_LIGHT_SPACE_MATRICES[(cascadeIndex + 1)] * vec4(1));
    (CASCADE_LIGHT_SPACE_MATRICES[(cascadeIndex + 1)] * vec4(1, 2, 3));
    (CASCADE_LIGHT_SPACE_MATRICES[((cascadeIndex + CASCADE_LIGHT_SPACE_MATRICES[(3 * 2)]) + 1)] * vec4(1, 2, 3));
    (CASCADE_LIGHT_SPACE_MATRICES[(((cascadeIndex + CASCADE_LIGHT_SPACE_MATRICES[(3 * 2)]) + 1) + CASCADE[2])] * vec4(1, 2, 3));
    (CASCADE_LIGHT_SPACE_MATRICES[(((cascadeIndex + CASCADE_LIGHT_SPACE_MATRICES[(3 * 2)]) + 1) + CASCADE[(2 + 3)])] * vec4(1, 2, 3));
}