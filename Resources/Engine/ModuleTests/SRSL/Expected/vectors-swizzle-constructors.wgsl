/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Compute

struct StorageBuffer_vout {
	vout : array<vec4<f32>>,
};
@group(0) @binding(0) var<storage, read_write> vout : StorageBuffer_vout;


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
    var a : vec2<f32> = vec2<f32>(1.0, 2.0);
    var b : vec3<f32> = vec3<f32>(a, 3.0);
    var c : vec4<f32> = vec4<f32>(b, 4.0);
    var xyz : vec3<f32> = c.xyz;
    var yx : vec2<f32> = a.yx;
    var zzzz : vec4<f32> = vec4<f32>(c.z);
    vout.vout[0] = c;
    vout.vout[1] = vec4<f32>(xyz, 1.0);
    vout.vout[2] = vec4<f32>(yx, yx);
    vout.vout[3] = zzzz;
}
