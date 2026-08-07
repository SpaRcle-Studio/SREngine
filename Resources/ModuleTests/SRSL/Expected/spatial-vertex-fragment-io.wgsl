/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Spatial

struct SHARED_t {
	// (64 bytes) private
	PROJECTION_MATRIX : mat4x4<f32>,
	// (64 bytes) private
	VIEW_MATRIX : mat4x4<f32>,
};
@group(0) @binding(0) var<uniform> SHARED : SHARED_t;

struct BLOCK_t {
	// (64 bytes) private
	MODEL_MATRIX : mat4x4<f32>,
	// (16 bytes) public
	TintColor : vec4<f32>,
};
@group(0) @binding(1) var<uniform> BLOCK : BLOCK_t;

@group(1) @binding(0) var Albedo : texture_2d<f32>;
@group(1) @binding(1) var Albedo_sampler : sampler;


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
	@location(4) _s_vUv : vec2<f32>,
};

var<private> VERTEX : vec3<f32>;
var<private> NORMAL : vec3<f32>;
var<private> TANGENT : vec4<f32>;
var<private> UV : vec2<f32>;

var<private> vUv : vec2<f32>;

struct FragmentOutput {
};

var<private> COLOR : vec4<f32>;

@vertex
fn vertex(input : VertexInput) -> VertexOutput {
    let PROJECTION_MATRIX : mat4x4<f32> = SHARED.PROJECTION_MATRIX;
    let VIEW_MATRIX : mat4x4<f32> = SHARED.VIEW_MATRIX;
    let MODEL_MATRIX : mat4x4<f32> = BLOCK.MODEL_MATRIX;
    var vsOut : VertexOutput;
    var OUT_POSITION : vec4<f32>;
    VERTEX = input.VERTEX_INPUT;
    NORMAL = input.NORMAL_INPUT;
    TANGENT = input.TANGENT_INPUT;
    UV = input.UV_INPUT;
    vUv = UV;
    var p : vec3<f32> = VERTEX;
    p = (p + (NORMAL * 0.01));
    VERTEX = (MODEL_MATRIX * vec4<f32>(p, 1.0)).xyz;
    OUT_POSITION = ((PROJECTION_MATRIX * VIEW_MATRIX) * vec4<f32>(VERTEX, 1.0));
    vsOut.position = OUT_POSITION;
    vsOut.VERTEX = VERTEX;
    vsOut.NORMAL = NORMAL;
    vsOut.TANGENT = TANGENT;
    vsOut.UV = UV;
    vsOut._s_vUv = vUv;
    return vsOut;
}

@fragment
fn fragment(fsIn : VertexOutput) -> FragmentOutput {
    let TintColor : vec4<f32> = BLOCK.TintColor;
    VERTEX = fsIn.VERTEX;
    NORMAL = fsIn.NORMAL;
    TANGENT = fsIn.TANGENT;
    UV = fsIn.UV;
    vUv = fsIn._s_vUv;
    var COLOR_INDEX_0 : vec4<f32>; /// location 0
    var COLOR_INDEX_1 : vec4<f32>; /// location 1
    var fsOut : FragmentOutput;
    var albedo : vec3<f32> = textureSample(Albedo, Albedo_sampler, vUv).rgb;
    COLOR = (vec4<f32>(albedo, 1.0) * TintColor);
    COLOR_INDEX_1 = vec4<f32>(fsIn.position.z);
    COLOR_INDEX_0 = COLOR;
    return fsOut;
}

