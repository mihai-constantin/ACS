#version 330

// TODO: get color value from vertex shader
in vec3 color;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO: write pixel out color
	out_color = vec4(color, 1);
}