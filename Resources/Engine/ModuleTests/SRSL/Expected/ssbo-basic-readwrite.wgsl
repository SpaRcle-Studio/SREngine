/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Compute

struct StorageBuffer_src {
	src : array<f32>,
};
@group(0) @binding(0) var<storage, read_write> src : StorageBuffer_src;

struct StorageBuffer_dst {
	dst : array<f32>,
};
@group(0) @binding(1) var<storage, read_write> dst : StorageBuffer_dst;


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
    var a : f32 = src.src[0];
    var b : f32 = src.src[1];
    var c : f32 = src.src[2];
    dst.dst[0] = (a + b);
    dst.dst[1] = (b * c);
    dst.dst[2] = max(a, c);
    dst.dst[3] = min(a, c);
}
