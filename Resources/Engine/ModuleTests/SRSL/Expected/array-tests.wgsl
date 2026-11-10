/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Compute

struct BLOCK_t {
	// (16 bytes) private
	NDC_RECT : vec4<f32>,
};
@group(0) @binding(0) var<uniform> BLOCK : BLOCK_t;


const array_case_1 : array<i32, 1> = array<i32, 1>(10);
const array_case_2 : array<array<i32, 16>, 1> = array<array<i32, 16>, 1>(array<i32, 16>(1, 2, 10, (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1)));
const case_1_1 : i32 = 123456u;

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

fn IsMaskIncludedSubMask(_sr_arg_mask : i32, _sr_arg_subMask : i32) -> bool {
    var mask : i32 = _sr_arg_mask;
    var subMask : i32 = _sr_arg_subMask;

    (((subMask & mask)) != (subMask));
    ((subMask) != ((subMask & mask)));
    ((subMask) == ((subMask & mask)));
    (((subMask & mask)) == (subMask));
    return (((subMask & mask)) == (subMask));

}

@compute @workgroup_size(1, 1, 1)
fn compute(@builtin(global_invocation_id) global_id : vec3<u32>, @builtin(workgroup_id) workgroup_id : vec3<u32>, @builtin(num_workgroups) num_workgroups : vec3<u32>, @builtin(local_invocation_id) local_id : vec3<u32>, @builtin(local_invocation_index) local_index : u32)  {
    let NDC_RECT : vec4<f32> = BLOCK.NDC_RECT;
    var sprite_vertices : array<vec2<f32>, 4> = array<vec2<f32>, 4>((NDC_RECT.xy + (vec2<f32>(0.0, 0.0) * NDC_RECT.zw)), (NDC_RECT.xy + (vec2<f32>(0.0, 1.0) * NDC_RECT.zw)), (NDC_RECT.xy + (vec2<f32>(1.0, 0.0) * NDC_RECT.zw)), (NDC_RECT.xy + (vec2<f32>(1.0, 1.0) * NDC_RECT.zw)));
    var value : bool = IsMaskIncludedSubMask();
    var case_1_2 : i32 = 1111u;
    case_1_2 = (case_1_2 + 123);
    case_1_2 = (case_1_2 + array_case_1[0]);
    case_1_2 = (case_1_2 + array_case_2[0][0]);
    case_1_2 = (case_1_2 + case_1_1);
    case_1_2 = (case_1_2 + ((case_1_1 + array_case_1[0]) + array_case_2[0][0]));
    var case_1 : i32 = ((array_case_1[0] + case_1_1) + case_1_2);
    var case_2 : i32 = array_case_2[0][0];
    var case_3 : i32 = 10;
    var case_4 : i32 = array(123);
    var case_5 : i32 = array(0x10, 0x20, 0x32);
    var case_6 : i32 = array(array(0x10, 0x20, 0x32), array(0x40, 0x50, 0x60));
    var case_7 : f32 = array(array(0.1, 0.2, 0.3), array(0.4, 0.5, 0.6));
    var case_8 : f32 = array(0.1);
}
