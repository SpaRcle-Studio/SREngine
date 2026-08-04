/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Compute

@group(0) @binding(0) var<storage, read_write> outv : array<vec4<f32>>;


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
    var a : vec3<f32> = vec3<f32>(1.0, 2.0, 3.0);
    var b : vec3<f32> = vec3<f32>((-2.0), 0.5, 4.0);
    var d : f32 = dot(a, b);
    var c : vec3<f32> = cross(a, b);
    var n : vec3<f32> = normalize((a + b));
    var l0 : f32 = length(a);
    var l1 : f32 = length(b);
    var l2 : f32 = length(c);
    outv[0] = vec4<f32>(d, l0, l1, l2);
    outv[1] = vec4<f32>(c, 1.0);
    outv[2] = vec4<f32>(n, 1.0);
    outv[3] = vec4<f32>(clamp(d, (-10.0), 10.0), smoothstep(0.0, 1.0, 0.25), step(0.5, 0.25), 1.0);
}
