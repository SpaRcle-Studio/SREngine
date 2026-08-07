/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Compute

struct StorageBuffer_items {
	itemsCount : u32,
	items : array<Item>,
};
@group(0) @binding(0) var<storage, read_write> items : StorageBuffer_items;

struct StorageBuffer_outv {
	outv : array<vec4<f32>>,
};
@group(0) @binding(1) var<storage, read_write> outv : StorageBuffer_outv;


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

fn Accumulate(idx : u32) -> vec4<f32> {
    var it : Item = items.items[idx];
    var w : f32 = max(0.0, it.weight);
    return ((it.color * w) + (vec4<f32>(it.pos, 1.0) * (1.0 - w)));

}

@compute @workgroup_size(1, 1, 1)
fn compute(@builtin(global_invocation_id) global_id : vec3<u32>, @builtin(workgroup_id) workgroup_id : vec3<u32>, @builtin(num_workgroups) num_workgroups : vec3<u32>, @builtin(local_invocation_id) local_id : vec3<u32>, @builtin(local_invocation_index) local_index : u32)  {
    let itemsCount : u32 = items.itemsCount;
    var idx0 : u32 = 0u;
    var idx1 : u32 = min(1u, items.itemsCount);
    var a : vec4<f32> = Accumulate(idx0);
    var b : vec4<f32> = Accumulate(idx1);
    outv.outv[0] = a;
    outv.outv[1] = b;
    outv.outv[2] = mix(a, b, 0.5);
}
