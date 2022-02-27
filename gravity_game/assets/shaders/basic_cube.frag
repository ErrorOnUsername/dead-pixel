#version 400 core

in vec3 pass_color;
in vec3 pass_fragment_position;
in vec3 pass_normal;

out vec4 out_color;

uniform vec3 u_light_position;

void main()
{
	vec3 norm = normalize(pass_normal);
	vec3 light_direction = normalize(u_light_position - pass_fragment_position);

	float diffuse_factor = max(dot(norm, light_direction), 0.0);
	vec3 diffuse = vec3(1.0, 1.0, 1.0) * diffuse_factor;

	vec3 result = diffuse * pass_color;

	out_color = vec4(result, 1.0);
}
