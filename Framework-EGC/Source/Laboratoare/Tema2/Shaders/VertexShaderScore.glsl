// CONSTANTIN MIHAI - 336CA

#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_textcoord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;
uniform float time;

// TODO: output values to fragment shader
out vec3 color;

void main()
{	
	color = object_color;
	 
	// compute gl_Position
	float x = v_position.x;
	float y = v_position.y;

	gl_Position = vec4(vec3(x, y, -1), 1);

	//gl_Position = Projection * View * Model * vec4(vec3(x, y, -1), 1);

}
