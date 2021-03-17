#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform float BloomIntensity;

uniform sampler2D image;
uniform bool horizontal;

const float weight[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

bool More(vec3 v1, vec3 v2){
    return (v1.r > v2.r && v1.g > v2.g && v1.b > v2.b);
}

void main() {
    vec2 tex_offset = BloomIntensity / textureSize(image, 0); // gets size of single texel
    vec3 result = texture(image, TexCoords).rgb * weight[0];

    if(horizontal)
    {
        for(int i = 1; i < 5; ++i) {
            result += texture(image, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(image, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(image, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }

   // if (result.a > 1)
   //     result.a = 1.0;
    //
   // if (result != vec3(0,0,0))
    //FragColor = vec4(result.rgb, 1);
    //if (result.a )

   // if (result.rgb == vec3(0,0,0))
    //if (More(result.rgb, vec3(0.03,0.03,0.03)))
    //if (dot(result.rgb, vec3(0.2126, 0.7152, 0.0722)) > 0.075)
    FragColor = vec4(result.rgb, 1);

    //FragColor = result;
}