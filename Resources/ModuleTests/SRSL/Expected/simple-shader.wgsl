/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Spatial

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

struct FragmentOutput {
};

var<private> COLOR : vec4<f32>;

@vertex
fn vertex(input : VertexInput) -> VertexOutput {
    var vsOut : VertexOutput;
    var OUT_POSITION : vec4<f32>;
    VERTEX = input.VERTEX;
    NORMAL = input.NORMAL;
    TANGENT = input.TANGENT;
    UV = input.UV;
    vsOut.VERTEX = VERTEX;
    vsOut.NORMAL = NORMAL;
    vsOut.TANGENT = TANGENT;
    vsOut.UV = UV;
    vsOut.position = OUT_POSITION;
    return vsOut;
}

fn fragment() -> stubType {
    var COLOR_INDEX_0 : vec4<f32>; /// location 0
    var COLOR_INDEX_1 : vec4<f32>; /// location 1
    var COLOR_INDEX_2 : vec4<f32>; /// location 2
    var fsOut : FragmentOutput;
    COLOR_INDEX_0 = COLOR;
    return fsOut;
}

