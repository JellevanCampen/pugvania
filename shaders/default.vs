#version 330 core
layout(location = 0) in vec3 vertex_pos_ms;

void main()
{
	gl_Position = vec4(vertex_pos_ms, 1.0);
}