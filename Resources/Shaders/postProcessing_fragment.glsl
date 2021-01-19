#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D scene;
uniform sampler2D bloomBlur;
uniform sampler2D skybox;

uniform float exposure;
uniform float gamma;

//uniform vec3 ColorCorrection;

void main()
{
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
    //float alpha = 1;

    if (sceneColor == vec3(0,0,0)) {
        hdrColor = skyboxColor;
    } else {
        hdrColor = sceneColor;
        float alpha = texture(scene, TexCoords).a;
        if (alpha != 1)
            hdrColor = (hdrColor * alpha) + skyboxColor;
    }

    hdrColor += texture(bloomBlur, TexCoords).rgb;

    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);

    //result.r *= ColorCorrection.r;
    //result.g *= ColorCorrection.g;
    //result.b *= ColorCorrection.b;

    // also gamma correct while we're at it
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1);
}