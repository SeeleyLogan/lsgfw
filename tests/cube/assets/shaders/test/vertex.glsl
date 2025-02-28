#version 430 core

layout(std430, binding = 0) buffer vertex_data
{
    vec4 vertices[];
};

layout(std430, binding = 1) buffer index_data
{
    uint indices[];
};

uniform mat4 vp;

out vec4 vert_color;

void main()
{
	vert_color = vertices[indices[gl_VertexID]*2+1];

	gl_Position = vp * vertices[indices[gl_VertexID]*2];
}