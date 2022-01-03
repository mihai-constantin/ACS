// CONSTANTIN MIHAI - 336CA

#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_textcoord;

// Uniform properties
uniform mat4 Model;
uniform vec3 object_color;

// combustible
uniform float combustible;
uniform int positionZ;

// output values to fragment shader
out vec3 color;

void main()
{	
	color = object_color;

	// compute gl_Position
	float x = v_position.x;
	float y = v_position.y;

	float combustible2 = min(combustible, 100.f);

	gl_Position = vec4(vec3(x - 0.5 * (1 - combustible2/100), y, -1), 1);

	// 0.5 * (combustible2/100)

}
