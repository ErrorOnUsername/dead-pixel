#version 400 core

in vec3 pass_pos;

out vec4 out_color;

#define LINE_WIDTH 0.52

void main()
{
	float x_mod = mod(pass_pos.x, 1.0);
	float grid_dist_x = max(x_mod, 1 - x_mod);

	float z_mod = mod(pass_pos.z, 1.0);
	float grid_dist_z = max(z_mod, 1 - z_mod);

	float p = (grid_dist_x <= LINE_WIDTH || grid_dist_z <= LINE_WIDTH) ? 1.0 : 0.0;
	out_color = vec4(p);
}
