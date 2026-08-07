/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Compute

struct BLOCK_t {
	// (8 bytes) private
	resolution : vec2<f32>,
};
@group(0) @binding(0) var<uniform> BLOCK : BLOCK_t;

struct StorageBuffer_outData {
	outData : array<f32>,
};
@group(0) @binding(1) var<storage, read_write> outData : StorageBuffer_outData;


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
    var rx : i32 = i32(resolution.x);
    var ry : i32 = i32(resolution.y);
    var fx : f32 = f32(rx);
    var fy : f32 = f32(ry);
    outData.outData[0] = (fx / max(1.0, resolution.x));
    outData.outData[1] = (fy / max(1.0, resolution.y));
    outData.outData[2] = f32(i32((fx + fy)));
}
