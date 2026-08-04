/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Compute

@group(0) @binding(0) var<storage, read_write> outv : array<i32>;


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

fn F(x : i32) -> i32 {
    return ((x * 2) + 1);

}

@compute @workgroup_size(1, 1, 1)
fn compute(@builtin(global_invocation_id) global_id : vec3<u32>, @builtin(workgroup_id) workgroup_id : vec3<u32>, @builtin(num_workgroups) num_workgroups : vec3<u32>, @builtin(local_invocation_id) local_id : vec3<u32>, @builtin(local_invocation_index) local_index : u32)  {
    var a : i32 = 2;
    var b : i32 = 3;
    var c : i32 = 4;
    var r0 : i32 = (a + (b * c));
    var r1 : i32 = ((a + b) * c);
    var r2 : i32 = (F(a) + (F(b) * F(c)));
    var r3 : i32 = ((a << 1) + ((b >> 1) * (c & 3)));
    var r4 : i32 = select((b + c), (b + c), ((a) == (2)));
    outv[0] = r0;
    outv[1] = r1;
    outv[2] = r2;
    outv[3] = r3;
    outv[4] = r4;
}
