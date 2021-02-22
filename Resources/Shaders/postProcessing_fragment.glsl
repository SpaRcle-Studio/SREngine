#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D scene;
uniform sampler2D bloomBlur;
uniform sampler2D skybox;
uniform sampler2D stencil;
uniform sampler2D depth;

//uniform float exposure;
//uniform float gamma;
//uniform float saturation;

uniform vec3 GammaExpSat;

uniform vec3 ColorCorrection;
uniform vec3 BloomColor;

float LinearizeDepth(float depth) {
    // преобразуем обратно в NDC
    float z = depth * 2.0 - 1.0;
    return (2.0 * 0.1 * 100.0) / (100.0 + 0.1 - z * (100.0 - 0.1));
}

void DrawStencil() {
    // outline thickness
    int w = 3;

    // if the pixel is black (we are on the silhouette)
    if (texture(stencil, TexCoords).a == 0) {
        vec2 size = 1.0f / textureSize(stencil, 0);

        for (int i = -w; i <= +w; i++)
            for (int j = -w; j <= +w; j++) {
                if (i == 0 && j == 0)
                 continue;

                vec2 offset = vec2(i, j) * size;

                // and if one of the pixel-neighbor is white (we are on the border)
                if (texture(stencil, TexCoords + offset).a == 1) {
                    //FragColor = vec4(vec3(1.0f), 1.0f);
                    FragColor = vec4(vec3(1, 1, 1), 1.0f);
                    return;
                }
            }
    }
}

void DrawStencilFast() {
    // and if one of the pixel-neighbor is white (we are on the border)
    if (texture(stencil, TexCoords).a == 1) {
        int w = 3;

        vec2 size = 1.0f / textureSize(stencil, 0);

        for (int i = -w; i <= +w; i++) {
            for (int j = -w; j <= +w; j++) {
                if (i == 0 && j == 0)
                    continue;

                if (texture(stencil, TexCoords + vec2(i, j) * size).a == 0) {
                    if (LinearizeDepth(gl_FragCoord.z) / 100 > texture(depth, TexCoords + vec2(i, j) * size).r)
                        FragColor = vec4(vec3(1, 1, 1), 1.0f);
                    else
                        FragColor = vec4(vec3(1, 0, 0), 1.0f);
                }
            }
        }

        return;
    }
}

vec3 czm_saturation(vec3 rgb, float adjustment)
{
    // Algorithm from Chapter 16 of OpenGL Shading Language
    const vec3 W = vec3(0.2125, 0.7154, 0.0721);
    vec3 intensity = vec3(dot(rgb, W));
    return mix(intensity, rgb, adjustment);
}

void main() {
    //vec3 hdrColor = texture(scene, TexCoords).rgb;
    //hdrColor += texture(bloomBlur, TexCoords).rgb; // additive blending

    //float alpha = texture(bloomBlur, TexCoords).a;
    //alpha += texture(scene, TexCoords).a;
    //if (alpha > 1)
    //    alpha = 1;

    vec3 sceneColor  = texture(scene,     TexCoords).rgb;
    vec3 skyboxColor = texture(skybox,    TexCoords).rgb;
    vec3 bloomColor  = texture(bloomBlur, TexCoords).rgb;

    vec3 hdrColor;

    if (sceneColor == vec3(0, 0, 0)) {
        hdrColor = skyboxColor;
    } else {
        hdrColor = sceneColor;
        float alpha = texture(scene, TexCoords).a;
        if (alpha != 1)
            hdrColor = (hdrColor * alpha) + skyboxColor;
    }

    hdrColor += texture(bloomBlur, TexCoords).rgb * BloomColor;

    hdrColor = czm_saturation(hdrColor, GammaExpSat.z);

    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * GammaExpSat.y);

    result *= ColorCorrection;

    // also gamma correct while we're at it
    result = pow(result, vec3(1.0 / GammaExpSat.x));
    FragColor = vec4(result, 1);

    DrawStencilFast();
}