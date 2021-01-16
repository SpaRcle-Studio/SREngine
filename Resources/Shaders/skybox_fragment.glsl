#version 330 core
//#version 130
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main() {    
    FragColor = texture(skybox, TexCoords);

    //vec4 color = gl_Color;

    //if (color.g > 0.5)
    //gl_FragColor = texture(skybox, TexCoords);
    //else
    //    gl_FragColor = color;
    //gl_FragColor = gl_Color;
}