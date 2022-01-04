#version 400 core

layout(location = 0) in vec4 in_position;
layout(location = 1) in vec4 in_color;

out vec4 pass_color;

uniform mat4 u_pv_matrix;

void main()
{
	pass_color = in_color;
	gl_Position = u_pv_matrix * in_position;
}
