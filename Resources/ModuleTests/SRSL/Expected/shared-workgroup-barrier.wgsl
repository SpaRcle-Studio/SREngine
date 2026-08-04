/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Compute

struct BLOCK_t {
	// (4 bytes) private
	elementCount : u32,
};
@group(0) @binding(0) var<uniform> BLOCK : BLOCK_t;

@group(0) @binding(1) var<storage, read_write> src : array<f32>;

@group(0) @binding(2) var<storage, read_write> dst : array<f32>;


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

var<workgroup> shData : array<f32, 64>;
@compute @workgroup_size(64, 1, 1)
fn compute(@builtin(global_invocation_id) global_id : vec3<u32>, @builtin(workgroup_id) workgroup_id : vec3<u32>, @builtin(num_workgroups) num_workgroups : vec3<u32>, @builtin(local_invocation_id) local_id : vec3<u32>, @builtin(local_invocation_index) local_index : u32)  {
    let elementCount : u32 = BLOCK.elementCount;
    var gid : u32 = global_id.x;
    var tid : u32 = local_index;
    shData[tid] = select(src[gid], src[gid], (gid < elementCount));
    barrier();
    for (var s : u32 = 32u; (s > 0u); s >>= 1u) {
        if ((tid < s)) {
            shData[tid] += shData[(tid + s)];
        }
        barrier();
    }
    if (((tid) == (0u))) {
        dst[workgroup_id.x] = shData[0];
    }
}
