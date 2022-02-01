#version 450

layout (location = 0) in vec3 inPos;

layout (location = 0) out vec3 UV;

layout (binding = 0) uniform SkyboxUBO {
    mat4 PVMat;
} sharedOBO;

void main() {
    UV = inPos;
    vec4 vPos = vec4(-inPos.x, inPos.y, inPos.z, 1.0);
    gl_Position = (sharedOBO.PVMat * vPos).xyww;
}
