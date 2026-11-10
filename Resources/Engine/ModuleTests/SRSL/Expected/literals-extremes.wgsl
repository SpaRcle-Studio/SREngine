/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Compute

struct StorageBuffer_nums {
	nums : array<u32>,
};
@group(0) @binding(0) var<storage, read_write> nums : StorageBuffer_nums;


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
    var a : f32 = 1e-6;
    var b : f32 = (1e + 3);
    var c : f32 = (-2.5e-2);
    var i0 : i32 = 0;
    var i1 : i32 = (-1);
    var i2 : i32 = 0x7FFFFFFF;
    var u0 : u32 = 0u;
    var u1 : u32 = 1u;
    var u2 : u32 = 0xFFFFFFFFu;
    nums.nums[0] = u32((a * 1000000.0));
    nums.nums[1] = u32(b);
    nums.nums[2] = u32((abs(c) * 1000.0));
    nums.nums[3] = u32(i0);
    nums.nums[4] = u32(i1);
    nums.nums[5] = u32(i2);
    nums.nums[6] = u0;
    nums.nums[7] = u1;
    nums.nums[8] = u2;
}
