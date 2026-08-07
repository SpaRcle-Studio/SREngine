/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Spatial

struct SHARED_t {
	// (64 bytes) private
	PROJECTION_MATRIX : mat4x4<f32>,
	// (64 bytes) private
	VIEW_MATRIX : mat4x4<f32>,
	// (12 bytes) private
	VIEW_DIRECTION : vec3<f32>,
	// (4 bytes) private
	TIME : f32,
};
@group(0) @binding(0) var<uniform> SHARED : SHARED_t;

struct BLOCK_t {
	// (64 bytes) private
	MODEL_MATRIX : mat4x4<f32>,
	// (12 bytes) public
	BubbleColor : vec3<f32>,
	// (4 bytes) public
	NoiseSampleSize : f32,
	// (4 bytes) public
	AnimationSpeed : f32,
	// (4 bytes) public
	HeightMultiplier : f32,
};
@group(0) @binding(1) var<uniform> BLOCK : BLOCK_t;

@group(1) @binding(0) var NoiseTex : texture_2d<f32>;
@group(1) @binding(1) var NoiseTex_sampler : sampler;


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
    let TIME : f32 = SHARED.TIME;
    let MODEL_MATRIX : mat4x4<f32> = BLOCK.MODEL_MATRIX;
    let NoiseSampleSize : f32 = BLOCK.NoiseSampleSize;
    let AnimationSpeed : f32 = BLOCK.AnimationSpeed;
    let HeightMultiplier : f32 = BLOCK.HeightMultiplier;
    var vsOut : VertexOutput;
    var OUT_POSITION : vec4<f32>;
    VERTEX = input.VERTEX_INPUT;
    NORMAL = input.NORMAL_INPUT;
    TANGENT = input.TANGENT_INPUT;
    UV = input.UV_INPUT;
    var height : f32 = textureSample(NoiseTex, NoiseTex_sampler, ((VERTEX.xz * (NoiseSampleSize / 100.0)) + (vec2<f32>(TIME) * (AnimationSpeed / 1000.0)))).r;
    VERTEX = (VERTEX + ((VERTEX * height) * HeightMultiplier));
    VERTEX = (MODEL_MATRIX * vec4<f32>(VERTEX, 1.0)).xyz;
    OUT_POSITION = ((PROJECTION_MATRIX * VIEW_MATRIX) * vec4<f32>(VERTEX, 1.0));
    vsOut.position = OUT_POSITION;
    vsOut.VERTEX = VERTEX;
    vsOut.NORMAL = NORMAL;
    vsOut.TANGENT = TANGENT;
    vsOut.UV = UV;
    return vsOut;
}

@fragment
fn fragment(fsIn : VertexOutput) -> FragmentOutput {
    let VIEW_MATRIX : mat4x4<f32> = SHARED.VIEW_MATRIX;
    let VIEW_DIRECTION : vec3<f32> = SHARED.VIEW_DIRECTION;
    let BubbleColor : vec3<f32> = BLOCK.BubbleColor;
    VERTEX = fsIn.VERTEX;
    NORMAL = fsIn.NORMAL;
    TANGENT = fsIn.TANGENT;
    UV = fsIn.UV;
    var COLOR_INDEX_0 : vec4<f32>; /// location 0
    var COLOR_INDEX_1 : vec4<f32>; /// location 1
    var COLOR_INDEX_2 : vec4<f32>; /// location 2
    var fsOut : FragmentOutput;
    var viewDirectionWorld : vec3<f32> = (VIEW_MATRIX * vec4<f32>(VIEW_DIRECTION, 0)).xyz;
    var normalWorld : vec3<f32> = (VIEW_MATRIX * vec4<f32>(NORMAL, 0.0)).xyz;
    COLOR = vec4<f32>(BubbleColor, Fresnel(viewDirectionWorld, normalWorld));
    COLOR_INDEX_1 = (vec4<f32>(fsIn.position.z) * max(0, (COLOR.a - 0.8)));
    COLOR_INDEX_2 = vec4<f32>(VERTEX, 1.0);
    COLOR_INDEX_0 = COLOR;
    return fsOut;
}

