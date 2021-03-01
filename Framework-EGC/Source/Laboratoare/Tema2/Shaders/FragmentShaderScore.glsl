// CONSTANTIN MIHAI - 336CA

#version 330

// get values from fragment shader
in vec3 frag_normal;

layout(location = 0) out vec4 out_color;

in vec3 color;

void main()
{
	// write pixel out color
	out_color = vec4(color, 1);
}