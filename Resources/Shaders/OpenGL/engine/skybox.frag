#version 450

layout (location = 4) out vec4 FragColor;

layout (location = 0) in vec3 UV;

uniform samplerCube skybox;

void main() {    
    FragColor = texture(skybox, UV);
}