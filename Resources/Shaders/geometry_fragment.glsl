#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoord;
    vec3 Normal;
} fs_in;

uniform int bloom;
uniform vec3 color;

uniform int hasDiffuse;

uniform sampler2D DiffuseMap;
//uniform sampler2D NormalMap;
//uniform sampler2D SpecularMap;

void main(){
    vec3 ambient = (hasDiffuse == 1 ? texture(DiffuseMap, fs_in.TexCoord).rgb : vec3(1.f,1.f,1.f)) * color;
    float alpha = texture(DiffuseMap, fs_in.TexCoord).a;

    //vec3 result = vec3(abs(fs_in.FragPos.x), abs(fs_in.FragPos.y), abs(fs_in.FragPos.z)); //ambient;
    vec3 result = ambient; //ambient;

    if (bloom == 1) {
        float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
        if (brightness > 1.0){
            BrightColor = vec4(result, alpha);
        }
        else
            BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);

    FragColor = vec4(result, alpha);
}