/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Compute

@group(0) @binding(0) var<storage, read_write> bits : array<u32>;


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
    var a : u32 = 0x0Fu;
    var b : u32 = 0xF0u;
    var andv : u32 = (a & b);
    var orv : u32 = (a | b);
    var xorv : u32 = (a ^ b);
    var notv : u32 = (~a);
    var shl : u32 = (a << 4u);
    var shr : u32 = (b >> 2u);
    bits[0] = andv;
    bits[1] = orv;
    bits[2] = xorv;
    bits[3] = notv;
    bits[4] = shl;
    bits[5] = shr;
}
