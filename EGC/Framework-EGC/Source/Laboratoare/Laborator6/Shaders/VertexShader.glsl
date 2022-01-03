#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_textcoord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform float time;

// TODO: output values to fragment shader
out vec3 color1;
out vec3 normal;
out vec3 timeColor;

void main()
{
	// TODO: send output to fragment shader
	color1 = v_color;
	normal = v_normal;
	timeColor = vec3(time, 0, 0);

	// TODO: compute gl_Position
	gl_Position = Projection * View * (vec4(0, time, 0, 0) + Model * vec4(v_position, 1));
}
