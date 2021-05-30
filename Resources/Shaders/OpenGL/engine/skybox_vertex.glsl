#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

//uniform mat4 projMat;
//uniform mat4 viewMat;
uniform mat4 PVmat;
uniform vec3 CamPos;

void main()
{
    /*
    TexCoords.x = aPos.x;
    TexCoords.y = aPos.y;
    TexCoords.z = aPos.z;

    vec4 pos = PVmat * vec4(aPos + vec3(CamPos.x, CamPos.y, -CamPos.z), 1.0);
    gl_Position = pos.xyww;
    */

    TexCoords = aPos;
    gl_Position = (PVmat * vec4(aPos + vec3(CamPos.x, CamPos.y, -CamPos.z), 1.0)).xyww;
}  