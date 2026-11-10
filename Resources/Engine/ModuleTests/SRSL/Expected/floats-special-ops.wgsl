/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Compute

struct StorageBuffer_outv {
	outv : array<f32>,
};
@group(0) @binding(0) var<storage, read_write> outv : StorageBuffer_outv;


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
    var a : f32 = 0.0;
    var b : f32 = 1.0;
    var c : f32 = (-1.0);
    var s0 : f32 = sign(c);
    var s1 : f32 = sign(b);
    var p : f32 = pow(2.0, 10.0);
    var e : f32 = exp2(5.0);
    var l : f32 = log2(32.0);
    outv.outv[0] = s0;
    outv.outv[1] = s1;
    outv.outv[2] = p;
    outv.outv[3] = e;
    outv.outv[4] = l;
    outv.outv[5] = mix(a, b, 0.25);
}
