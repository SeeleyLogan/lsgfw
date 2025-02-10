#version 330 core

in vec4 vert_color;
in vec3 surface_normal;

out vec4 frag_color;

void main()
{
	frag_color = vert_color;
}

