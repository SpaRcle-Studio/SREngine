#version 330 core

layout (location = 0) out vec4 FragColor;

uniform int id;

void main() {
    float r = ((id + 1 >> 16) & 0xFF);  // Extract the RR byte
    float g = ((id + 1 >> 8) & 0xFF);   // Extract the GG byte
    float b = ((id + 1) & 0xFF);        // Extract the BB byte

    FragColor = vec4(r, g, b, 255) / 255.f;
}