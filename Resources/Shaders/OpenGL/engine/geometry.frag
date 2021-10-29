//#version 330 core
#version 410 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;
layout (location = 2) out vec4 DepthColor;
layout (location = 3) out vec4 StencilMask;

layout (location = 0) in vec2 TexCoord;

uniform vec3 color;
uniform ivec2 config;
uniform sampler2D DiffuseMap;

float LinearizeDepth(float depth) {
    // преобразуем обратно в NDC
    float z = depth * 2.0 - 1.0;
    return (2.0 * 0.1 * 100.0) / (100.0 + 0.1 - z * (100.0 - 0.1));
}

void main() {
    //vec3 ambient = (hasDiffuse == 1 ? texture(DiffuseMap, fs_in.TexCoord).rgb : vec3(1.f,1.f,1.f)) * color;
    vec3 ambient = texture(DiffuseMap, TexCoord).rgb * color;
    float alpha = texture(DiffuseMap, TexCoord).a;

    vec3 result = ambient; //ambient;

    //float gray = dot(result.rgb, vec3(0.299, 0.587, 0.114));
    //result -= result / vec3(gray); // interesting effect

    if (config.y == 0)
        StencilMask = vec4(0, 0, 0, 0);
    else {
        if (config.y == 1)
            StencilMask = vec4(1, 1, 1, 1);
        else if (config.y == 2)
            StencilMask = vec4(1, 0, 0, 1);
        else if (config.y == 3)
            StencilMask = vec4(0, 1, 0, 1);
        else if (config.y == 4)
            StencilMask = vec4(0, 0, 1, 1);
    }

    if (config.x == 1) {
        float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
        if (brightness > 1.0)
            BrightColor = vec4(result, alpha);
        else
            BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);

    DepthColor = vec4(vec3(LinearizeDepth(gl_FragCoord.z) / 100), 1);

    //if (fract(vertexID) < 0.1)
        FragColor = vec4(result, alpha);// * vec4(fs_in.VColor, 1);
}