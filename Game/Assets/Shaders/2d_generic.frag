#version 460

in vec4 pass_color;
in vec2 pass_tex_coords;

out vec4 out_color;

void main()
{
	out_color = pass_color;
}
