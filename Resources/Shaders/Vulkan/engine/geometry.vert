#version 450

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inUV;
layout (location = 2) in vec3 inNorm;
layout (location = 3) in vec3 inTang;
layout (location = 4) in vec3 inBitang;

layout (location = 0) out vec2 TexCoord;
layout (location = 1) out vec4 Color;

layout (binding = 0) uniform MeshUBO {
    mat4 model;
    vec4 color;
} meshUBO;

layout (binding = 1) uniform ProjViewUBO {
    mat4 proj;
    mat4 view;
} sharedUBO;

#extension GL_ARB_separate_shader_objects : enable

vec3 quat_mul_vec3( vec4 q, vec3 v ) { return v + (2.0 * cross(q.xyz, cross(q.xyz, v) + (q.w * v))); }

vec4 quat_mul(vec4 q1, vec4 q2) {
    return vec4(q2.xyz * q1.w + q1.xyz * q2.w + cross(q1.xyz, q2.xyz), q1.w * q2.w - dot(q1.xyz, q2.xyz) );
}

vec4 quat_axis_angle( vec3 axis, float angle ) { return vec4( axis * sin( angle * 0.5 ), cos( angle * 0.5 ) ); }

void main() {
    TexCoord = inUV;
    Color = meshUBO.color;

    vec4 vPos = vec4(-inPos.x, inPos.y, inPos.z, 1.0);
    gl_Position = sharedUBO.proj * sharedUBO.view * meshUBO.model * vPos;
}