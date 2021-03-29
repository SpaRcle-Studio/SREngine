#version 410
//#extension GL_KHR_vulkan_glsl : enable

//layout (location = 0) in vec3 aPos;

uniform mat4 projMat;
uniform mat4 viewMat;

layout(location = 1) out vec3 nearPoint;
layout(location = 2) out vec3 farPoint;

layout(location = 3) out mat4 fragView;
layout(location = 7) out mat4 fragProj;

//vec3 gridPlane[6] = vec3[](
//    vec3(1, 1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
//    vec3(-1, -1, 0), vec3(1, 1, 0), vec3(1, -1, 0)
//);

vec3 gridPlane[6] = vec3[](
    vec3(-1, 1, 0), vec3(-1, -1, 0), vec3(1, 1, 0),
    vec3(1, -1, 0), vec3(1, 1, 0), vec3(-1, -1, 0)
);

vec3 UnprojectPoint(float x, float y, float z, mat4 view, mat4 projection) {
    mat4 viewInv = inverse(view);
    mat4 projInv = inverse(projection);
    vec4 unprojectedPoint =  viewInv * projInv * vec4(x, y, z, 1.0);
    return unprojectedPoint.xyz / unprojectedPoint.w;
}

void main() {
    fragProj = projMat;
    fragView = viewMat;

    vec3 p = gridPlane[gl_VertexID].xyz;
    nearPoint = UnprojectPoint(p.x, p.y, 0.0, viewMat, projMat).xyz; // unprojecting on the near plane
    farPoint = UnprojectPoint(p.x, p.y, 1.0, viewMat, projMat).xyz; // unprojecting on the far plane
    gl_Position = vec4(p, 1.0); // using directly the clipped coordinates

    //gl_Position = projMat * viewMat * vec4(gridPlane[gl_VertexID].xyz, 1.0);
}
