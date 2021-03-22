#version 420 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;

out VS_OUT {
    vec3 FragPos;
    vec2 TexCoord;
    vec3 Normal;
} vs_out;

//out float vertexID;

uniform mat4 PVmat;
uniform mat4 modelMat;

void main() {
    //vertexID = float(gl_VertexID);
    //gl_Position = projMat * viewMat * vec4(vs_out.FragPos, 1.0);


    vs_out.FragPos = vec3(modelMat * vec4(aPosition, 1.0));
    vs_out.TexCoord  = vec2(aTexCoord.x, 1 - aTexCoord.y); // flip the texture along the Y axis
    gl_Position = PVmat * vec4(vs_out.FragPos, 1.0);
}

/*b
    mat4x4 proj = mat4x4(
        vec4(1.357995, 0.000000, 0.000000, 0.000000),
        vec4(0.000000, 2.414213, 0.000000, 0.000000),
        vec4(0.000000, 0.000000, -1.000025, -1.000000),
        vec4(0.000000, 0.000000, -0.200003, 0.000000)
    );
*/