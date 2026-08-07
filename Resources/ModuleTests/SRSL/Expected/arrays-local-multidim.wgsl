/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Compute

struct StorageBuffer_outv {
	outv : array<i32>,
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
    var a : int[4] = array(1, 2, 3, 4);
    var b : int[2][2] = array(array(10, 11), array(20, 21));
    var c : float[2][3] = array(array(0.1, 0.2, 0.3), array(1.1, 1.2, 1.3));
    var idx : i32 = ((a[0] + a[3]) - 3);
    var v0 : i32 = a[idx];
    var v1 : i32 = (b[0][1] + b[1][0]);
    var v2 : i32 = i32((c[1][2] * 10.0));
    outv.outv[0] = v0;
    outv.outv[1] = v1;
    outv.outv[2] = v2;
}
