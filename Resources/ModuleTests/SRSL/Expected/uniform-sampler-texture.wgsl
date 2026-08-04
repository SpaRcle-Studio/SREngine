/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Compute

struct BLOCK_t {
	// (8 bytes) private
	resolution : vec2<f32>,
};
@group(0) @binding(0) var<uniform> BLOCK : BLOCK_t;

@group(0) @binding(1) var<storage, read_write> outv : array<vec4<f32>>;

@group(1) @binding(0) var inputTex : texture_2d<f32>;
@group(1) @binding(1) var inputTex_sampler : sampler;


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
    let resolution : vec2<f32> = BLOCK.resolution;
    var gid : vec2<i32> = vec2<i32>(global_id.xy);
    var uv : vec2<f32> = ((vec2<f32>(gid) + 0.5) / max(vec2<f32>(1.0), resolution));
    var rgb : vec3<f32> = textureSample(inputTex, uv).rgb;
    var lum : f32 = max(dot(rgb, vec3<f32>(0.2126, 0.7152, 0.0722)), 1e-6);
    outv[0] = vec4<f32>(rgb, 1.0);
    outv[1] = vec4<f32>(lum, lum, lum, 1.0);
}
