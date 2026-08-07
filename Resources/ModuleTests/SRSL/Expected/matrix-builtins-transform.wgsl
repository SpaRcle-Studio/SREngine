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
	// (4 bytes) public
	Scale : f32,
};
@group(0) @binding(1) var<uniform> BLOCK : BLOCK_t;


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
    let PROJECTION_MATRIX : mat4x4<f32> = SHARED.PROJECTION_MATRIX;
    let VIEW_MATRIX : mat4x4<f32> = SHARED.VIEW_MATRIX;
    let MODEL_MATRIX : mat4x4<f32> = BLOCK.MODEL_MATRIX;
    let Scale : f32 = BLOCK.Scale;
    var vsOut : VertexOutput;
    var OUT_POSITION : vec4<f32>;
    VERTEX = input.VERTEX_INPUT;
    NORMAL = input.NORMAL_INPUT;
    TANGENT = input.TANGENT_INPUT;
    UV = input.UV_INPUT;
    var p : vec3<f32> = (VERTEX * Scale);
    var world : vec4<f32> = (MODEL_MATRIX * vec4<f32>(p, 1.0));
    var view : vec4<f32> = (VIEW_MATRIX * world);
    OUT_POSITION = (PROJECTION_MATRIX * view);
    VERTEX = world.xyz;
    vsOut.position = OUT_POSITION;
    vsOut.VERTEX = VERTEX;
    vsOut.NORMAL = NORMAL;
    vsOut.TANGENT = TANGENT;
    vsOut.UV = UV;
    return vsOut;
}

@fragment
fn fragment(fsIn : VertexOutput) -> FragmentOutput {
    VERTEX = fsIn.VERTEX;
    NORMAL = fsIn.NORMAL;
    TANGENT = fsIn.TANGENT;
    UV = fsIn.UV;
    var COLOR_INDEX_0 : vec4<f32>; /// location 0
    var fsOut : FragmentOutput;
    COLOR = vec4<f32>(((NORMAL * 0.5) + 0.5), 1.0);
    COLOR_INDEX_0 = COLOR;
    return fsOut;
}

