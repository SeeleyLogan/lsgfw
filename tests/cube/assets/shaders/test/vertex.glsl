#version 430 core

layout(std430, binding = 0) buffer vertex_data
{
    vec4 vertices[];
};

layout(std430, binding = 1) buffer index_data
{
    uint indices[];
};


void main()
{
    gl_Position = vertices[indices[gl_VertexID]];
}

