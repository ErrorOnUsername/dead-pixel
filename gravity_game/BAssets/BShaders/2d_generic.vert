#version 460

layout(location = 0)in vec3  in_position
layout(location = 1)in vec2  in_tex_coords
layout(location = 2)in vec4  in_color
layout(location = 3)in float in_texture_index
layout(location = 4)in float in_texture_tiling_factor

out vec4 pass_color;
out vec2 pass_tex_coords;

uniform mat4 u_view_projection_matrix;
uniform mat4 u_transform_matrix;

void main()
{
	gl_Position = u_view_projection_matrix
	            * u_transform_matrix
	            * vec4(in_position, 1.0);

	pass_color = in_color;
	pass_tex_coord = in_tex_coords;
}
