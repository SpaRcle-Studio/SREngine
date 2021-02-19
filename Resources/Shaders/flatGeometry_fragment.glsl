#version 330 core

layout (location = 0) out vec4 FragColor;

uniform int id;

void main() {
    int _id = id + 1;

    float r = ((_id >> 16) & 0xFF);  // Extract the RR byte
    float g = ((_id >> 8) & 0xFF);   // Extract the GG byte
    float b = ((_id) & 0xFF);        // Extract the BB byte

    FragColor = vec4(r, g, b, 255) / 255.f;
}