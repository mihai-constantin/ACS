#version 330

// TODO: get values from fragment shader
in vec3 frag_normal;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

layout(location = 0) out vec3 color;

in vec3 color1;
in vec3 normal;
in vec3 timeColor;

void main()
{
	// TODO: write pixel out color
	// out_color = vec4(1);

	color = abs(normal + timeColor);
}