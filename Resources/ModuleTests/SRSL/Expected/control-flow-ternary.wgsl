/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Compute

struct BLOCK_t {
	// (4 bytes) private
	threshold : i32,
};
@group(0) @binding(0) var<uniform> BLOCK : BLOCK_t;

struct StorageBuffer_outBuf {
	outBuf : array<i32>,
};
@group(0) @binding(1) var<storage, read_write> outBuf : StorageBuffer_outBuf;


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

fn SelectValue(x : i32, y : i32) -> i32 {
    return select(x, x, (x > y));

}

@compute @workgroup_size(1, 1, 1)
fn compute(@builtin(global_invocation_id) global_id : vec3<u32>, @builtin(workgroup_id) workgroup_id : vec3<u32>, @builtin(num_workgroups) num_workgroups : vec3<u32>, @builtin(local_invocation_id) local_id : vec3<u32>, @builtin(local_invocation_index) local_index : u32)  {
    let threshold : i32 = BLOCK.threshold;
    var x : i32 = 5;
    var y : i32 = 7;
    var m : i32 = SelectValue(x, y);
    var r0 : i32 = select((m + 1), (m + 1), (m >= threshold));
    var r1 : i32 = select((x + y), (x + y), ((x + y) > 0));
    outBuf.outBuf[0] = r0;
    outBuf.outBuf[1] = r1;
}
