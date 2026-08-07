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

fn ClampInt(v : i32, lo : i32, hi : i32) -> i32 {
    if ((v < lo)) {
        return lo;

    }
    if ((v > hi)) {
        return hi;

    }
    return v;

}

fn Fib(n : i32) -> i32 {
    if ((n <= 1)) {
        return n;

    }
    return (Fib((n - 1)) + Fib((n - 2)));

}

@compute @workgroup_size(1, 1, 1)
fn compute(@builtin(global_invocation_id) global_id : vec3<u32>, @builtin(workgroup_id) workgroup_id : vec3<u32>, @builtin(num_workgroups) num_workgroups : vec3<u32>, @builtin(local_invocation_id) local_id : vec3<u32>, @builtin(local_invocation_index) local_index : u32)  {
    var a : i32 = ClampInt((-10), 0, 5);
    var b : i32 = ClampInt(123, 0, 5);
    var c : i32 = ClampInt(3, 0, 5);
    var f : i32 = Fib(7);
    outv.outv[0] = a;
    outv.outv[1] = b;
    outv.outv[2] = c;
    outv.outv[3] = f;
}
