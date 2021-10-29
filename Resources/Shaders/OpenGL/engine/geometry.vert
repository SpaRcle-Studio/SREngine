#version 420 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;

layout (location = 0) out vec2 TexCoord;

uniform mat4 PVmat;
uniform mat4 modelMat;

void main() {
    vec3 FragPos = vec3(modelMat * vec4(aPosition, 1.0));
    TexCoord = vec2(aTexCoord.x, aTexCoord.y); // flip the texture along the Y axis
    gl_Position = PVmat * vec4(FragPos, 1.0);
}
