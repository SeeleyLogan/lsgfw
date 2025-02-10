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
out vec4 surface_normal;

void main()
{
	vert_color = vertices[indices[gl_VertexID]*2+1];
	
	vec4 a = vertices[indices[gl_VertexID - gl_VertexID % 3]     * 2];
	vec4 b = vertices[indices[gl_VertexID - gl_VertexID % 3 + 1] * 2];
	vec4 c = vertices[indices[gl_VertexID - gl_VertexID % 3 + 2] * 2];
	
	surface_normal = cross(b - a, c - a);

	gl_Position = vp * vertices[indices[gl_VertexID]*2];
}

