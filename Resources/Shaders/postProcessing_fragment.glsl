#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D scene;
uniform sampler2D bloomBlur;

uniform float exposure;
uniform float gamma;

//uniform vec3 ColorCorrection;

void main()
{
    vec3 hdrColor = texture(scene, TexCoords).rgb;
    hdrColor += texture(bloomBlur, TexCoords).rgb; // additive blending

    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);

    //result.r *= ColorCorrection.r;
    //result.g *= ColorCorrection.g;
    //result.b *= ColorCorrection.b;

    // also gamma correct while we're at it
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0);
}