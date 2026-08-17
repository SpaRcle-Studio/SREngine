/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader type: Skybox

struct SHARED_t {
	// (64 bytes) private
	PROJECTION_MATRIX : mat4x4<f32>,
	// (64 bytes) private
	VIEW_NO_TRANSLATE_MATRIX : mat4x4<f32>,
	// (12 bytes) private
	DIRECTIONAL_LIGHT_DIRECTION : vec3<f32>,
	// (12 bytes) private
	GROUND_COLOR : vec3<f32>,
	// (12 bytes) private
	SKY_COLOR : vec3<f32>,
	// (12 bytes) private
	SUN_COLOR : vec3<f32>,
	// (4 bytes) private
	SUN_INTENSITY : f32,
};
@group(0) @binding(0) var<uniform> SHARED : SHARED_t;


const SUN_HALO_SIZE : f32 = 0.018;
const SUN_HALO_SOFTNESS : f32 = 0.018;

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
    let VIEW_NO_TRANSLATE_MATRIX : mat4x4<f32> = SHARED.VIEW_NO_TRANSLATE_MATRIX;
    var vsOut : VertexOutput;
    var OUT_POSITION : vec4<f32>;
    VERTEX = input.VERTEX_INPUT;
    NORMAL = input.NORMAL_INPUT;
    TANGENT = input.TANGENT_INPUT;
    UV = input.UV_INPUT;
    OUT_POSITION = ((PROJECTION_MATRIX * VIEW_NO_TRANSLATE_MATRIX) * vec4<f32>(VERTEX, 1.0)).xyww;
    vsOut.position = OUT_POSITION;
    vsOut.VERTEX = VERTEX;
    vsOut.NORMAL = NORMAL;
    vsOut.TANGENT = TANGENT;
    vsOut.UV = UV;
    return vsOut;
}

@fragment
fn fragment(fsIn : VertexOutput) -> FragmentOutput {
    let DIRECTIONAL_LIGHT_DIRECTION : vec3<f32> = SHARED.DIRECTIONAL_LIGHT_DIRECTION;
    let GROUND_COLOR : vec3<f32> = SHARED.GROUND_COLOR;
    let SKY_COLOR : vec3<f32> = SHARED.SKY_COLOR;
    let SUN_COLOR : vec3<f32> = SHARED.SUN_COLOR;
    let SUN_INTENSITY : f32 = SHARED.SUN_INTENSITY;
    VERTEX = fsIn.VERTEX;
    NORMAL = fsIn.NORMAL;
    TANGENT = fsIn.TANGENT;
    UV = fsIn.UV;
    var COLOR_INDEX_0 : vec4<f32>; /// location 0
    var COLOR_INDEX_1 : vec4<f32>; /// location 1
    var COLOR_INDEX_2 : vec4<f32>; /// location 2
    var COLOR_INDEX_3 : vec4<f32>; /// location 3
    var fsOut : FragmentOutput;
    var eyeDir : vec3<f32> = normalize(VERTEX);
    var col : f32 = clamp(((eyeDir.y + 0.035) / 0.05), 0.0, 1.0);
    var color : vec3<f32> = mix(GROUND_COLOR, SKY_COLOR, col);
    var sunDir : vec3<f32> = normalize((-DIRECTIONAL_LIGHT_DIRECTION));
    var angle : f32 = acos(clamp(dot(eyeDir, sunDir), (-1.0), 1.0));
    var sunGlow : f32 = smoothstep((SUN_HALO_SIZE + SUN_HALO_SOFTNESS), SUN_HALO_SIZE, angle);
    var halo : f32 = exp(((-angle) * 100.0));
    var sunPeak : f32 = pow(clamp((1.0 - (angle / (SUN_HALO_SIZE * 32.0))), 0.0, 1.0), 3.0);
    var sun : vec3<f32> = ((SUN_COLOR * SUN_INTENSITY) * ((sunGlow + (0.15 * halo)) + (0.5 * sunPeak)));
    color = (color + sun);
    color = mix(color, (color * vec3<f32>(0.9, 0.95, 1.0)), pow(eyeDir.y, 2.0));
    COLOR = vec4<f32>(color, 1.0);
    COLOR_INDEX_1 = vec4<f32>(0.0);
    COLOR_INDEX_2 = vec4<f32>(0.0);
    COLOR_INDEX_3 = vec4<f32>(0.0);
    COLOR_INDEX_0 = COLOR;
    return fsOut;
}

