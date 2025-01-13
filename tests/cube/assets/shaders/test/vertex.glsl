#version 430 core

layout(std430, binding = 0) buffer data
{
    vec4 vertices[];
};

void main()
{
    gl_Position = vertices[gl_VertexID];
}

