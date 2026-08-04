/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Line

struct SHARED_t {
	// (64 bytes) private
	PROJECTION_MATRIX : mat4x4<f32>,
	// (64 bytes) private
	VIEW_MATRIX : mat4x4<f32>,
};
@group(0) @binding(0) var<uniform> SHARED : SHARED_t;

@group(0) @binding(1) var<storage, read_write> lines : array<vec3<f32>>;


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
	@location(4) _s_lineColor : vec4<f32>,
};

var<private> VERTEX : vec3<f32>;
var<private> NORMAL : vec3<f32>;
var<private> TANGENT : vec4<f32>;
var<private> UV : vec2<f32>;

var<private> lineColor : vec4<f32>;

struct FragmentOutput {
};

var<private> COLOR : vec4<f32>;

@vertex
fn vertex(input : VertexInput, @builtin(vertex_index) vertexIndex : u32) -> VertexOutput {
    let PROJECTION_MATRIX : mat4x4<f32> = SHARED.PROJECTION_MATRIX;
    let VIEW_MATRIX : mat4x4<f32> = SHARED.VIEW_MATRIX;
    var vsOut : VertexOutput;
    var OUT_POSITION : vec4<f32>;
    VERTEX = input.VERTEX_INPUT;
    NORMAL = input.NORMAL_INPUT;
    TANGENT = input.TANGENT_INPUT;
    UV = input.UV_INPUT;
    var VERTEX_INDEX : u32 = vertexIndex;
    var idx : u32 = ((gl_InstanceIndex * 2u) + u32(VERTEX_INDEX));
    var p : vec3<f32> = points[idx];
    lineColor = vec4<f32>(abs(p), 1.0);
    OUT_POSITION = ((PROJECTION_MATRIX * VIEW_MATRIX) * vec4<f32>(p, 1.0));
    vsOut.position = OUT_POSITION;
    vsOut.VERTEX = VERTEX;
    vsOut.NORMAL = NORMAL;
    vsOut.TANGENT = TANGENT;
    vsOut.UV = UV;
    vsOut._s_lineColor = lineColor;
    return vsOut;
}

@fragment
fn fragment(fsIn : VertexOutput)  {
    VERTEX = fsIn.VERTEX;
    NORMAL = fsIn.NORMAL;
    TANGENT = fsIn.TANGENT;
    UV = fsIn.UV;
    lineColor = fsIn._s_lineColor;
    var COLOR_INDEX_0 : vec4<f32>; /// location 0
    var fsOut : FragmentOutput;
    COLOR = lineColor;
    COLOR_INDEX_0 = COLOR;
    return fsOut;
}

