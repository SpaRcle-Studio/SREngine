/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Compute

struct SHARED_t {
	// (256 bytes) private
	CASCADE_LIGHT_SPACE_MATRICES : array<mat4x4<f32>, 4>,
};
@group(0) @binding(0) var<uniform> SHARED : SHARED_t;


struct VertexInput {
	@location(0) VERTEX_INPUT : vec3<f32>,
	@location(1) NORMAL_INPUT : vec3<f32>,
	@location(2) TANGENT_INPUT : vec4<f32>,
	@location(3) UV_INPUT : vec2<f32>,
};

struct VertexOutput {
	@builtin(position) position : vec4<f32>,
	@location(0) VERTEX : vec3<f32>,
	@location(1) NORMAL : vec3<f32>,
	@location(2) TANGENT : vec4<f32>,
	@location(3) UV : vec2<f32>,
};

var<private> VERTEX : vec3<f32>;
var<private> NORMAL : vec3<f32>;
var<private> TANGENT : vec4<f32>;
var<private> UV : vec2<f32>;

@compute @workgroup_size(1, 1, 1)
fn compute(@builtin(global_invocation_id) global_id : vec3<u32>, @builtin(workgroup_id) workgroup_id : vec3<u32>, @builtin(num_workgroups) num_workgroups : vec3<u32>, @builtin(local_invocation_id) local_id : vec3<u32>, @builtin(local_invocation_index) local_index : u32)  {
    let CASCADE_LIGHT_SPACE_MATRICES : mat4x4<f32> = SHARED.CASCADE_LIGHT_SPACE_MATRICES;
    (CASCADE_LIGHT_SPACE_MATRICES[cascadeIndex] * vec4<f32>());
    (CASCADE_LIGHT_SPACE_MATRICES[cascadeIndex] * vec4<f32>(1));
    (CASCADE_LIGHT_SPACE_MATRICES[cascadeIndex] * vec4<f32>(1, 2, 3));
    (CASCADE_LIGHT_SPACE_MATRICES[(cascadeIndex + 1)] * vec4<f32>());
    (CASCADE_LIGHT_SPACE_MATRICES[(cascadeIndex + 1)] * vec4<f32>(1));
    (CASCADE_LIGHT_SPACE_MATRICES[(cascadeIndex + 1)] * vec4<f32>(1, 2, 3));
    (CASCADE_LIGHT_SPACE_MATRICES[((cascadeIndex + CASCADE_LIGHT_SPACE_MATRICES[(3 * 2)]) + 1)] * vec4<f32>(1, 2, 3));
    (CASCADE_LIGHT_SPACE_MATRICES[(((cascadeIndex + CASCADE_LIGHT_SPACE_MATRICES[(3 * 2)]) + 1) + CASCADE[2])] * vec4<f32>(1, 2, 3));
    (CASCADE_LIGHT_SPACE_MATRICES[(((cascadeIndex + CASCADE_LIGHT_SPACE_MATRICES[(3 * 2)]) + 1) + CASCADE[(2 + 3)])] * vec4<f32>(1, 2, 3));
}
