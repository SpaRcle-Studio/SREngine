/// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]

/// Shader stage: Fragment
/// Shader type: Skybox

#version 450

const float SUN_HALO_SIZE = 0.018;

const float SUN_HALO_SOFTNESS = 0.018;


layout (std140, binding = 0) uniform SHARED {
	// (64 bytes) private
	mat4 PROJECTION_MATRIX;
	// (64 bytes) private
	mat4 VIEW_NO_TRANSLATE_MATRIX;
	// (12 bytes) private
	vec3 DIRECTIONAL_LIGHT_DIRECTION;
	// (12 bytes) private
	vec3 GROUND_COLOR;
	// (12 bytes) private
	vec3 SKY_COLOR;
	// (12 bytes) private
	vec3 SUN_COLOR;
	// (4 bytes) private
	float SUN_INTENSITY;
};

vec4 COLOR;

vec4 COLOR_INDEX_0; /// emulate location 0
vec4 COLOR_INDEX_1; /// emulate location 1
vec4 COLOR_INDEX_2; /// emulate location 2
vec4 COLOR_INDEX_3; /// emulate location 3

void main() {
    vec3 eyeDir = normalize(VERTEX);
    float col = clamp(((eyeDir.y + 0.035) / 0.05), 0.0, 1.0);
    vec3 color = mix(GROUND_COLOR, SKY_COLOR, col);
    vec3 sunDir = normalize((-DIRECTIONAL_LIGHT_DIRECTION));
    float angle = acos(clamp(dot(eyeDir, sunDir), (-1.0), 1.0));
    float sunGlow = smoothstep((SUN_HALO_SIZE + SUN_HALO_SOFTNESS), SUN_HALO_SIZE, angle);
    float halo = exp(((-angle) * 100.0));
    float sunPeak = pow(clamp((1.0 - (angle / (SUN_HALO_SIZE * 32.0))), 0.0, 1.0), 3.0);
    vec3 sun = ((SUN_COLOR * SUN_INTENSITY) * ((sunGlow + (0.15 * halo)) + (0.5 * sunPeak)));
    (color += sun);
    color = mix(color, (color * vec3(0.9, 0.95, 1.0)), pow(eyeDir.y, 2.0));
    COLOR = vec4(color, 1.0);
    COLOR_INDEX_1 = vec4(0.0);
    COLOR_INDEX_2 = vec4(0.0);
    COLOR_INDEX_3 = vec4(0.0);

    COLOR_INDEX_0 = COLOR;
}