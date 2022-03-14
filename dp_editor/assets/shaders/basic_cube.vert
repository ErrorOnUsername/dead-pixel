#version 400 core

layout(location = 0) in vec3  in_position;
layout(location = 1) in float in_color;
layout(location = 2) in vec3  in_normal;

out vec3 pass_color;
out vec3 pass_fragment_position;
out vec3 pass_normal;

uniform mat4 u_pv_matrix;
uniform mat4 u_transform_matrix;

void main()
{
	pass_color  = vec3(0.0, in_color, in_color);
	gl_Position = u_pv_matrix * u_transform_matrix * vec4(in_position, 1.0);

	pass_fragment_position = vec3(u_transform_matrix * vec4(in_position, 1.0));
	pass_normal            = mat3(transpose(inverse(u_transform_matrix))) * in_normal;
}
