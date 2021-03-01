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

// Uniforms for light properties
uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// TODO: output values to fragment shader
out vec3 color;

void main()
{	
	// compute world space vectors
	vec3 world_pos = (Model * vec4(v_position, 1)).xyz;
	vec3 world_normal = normalize( mat3(Model) * normalize(v_normal) );

	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_pos);
	vec3 V = normalize(eye_position - world_pos);
	vec3 H = normalize(L + V);

	// define ambient light component
	float ambient_light = 0.25;

	// compute diffuse light component
	float diffuse_light = material_kd * max (dot(N, L), 0);

	float specular_light = 0;

	if (diffuse_light > 0)
	{
		specular_light = material_ks * pow(max(dot(normalize(N), H), 0), material_shininess);
	}

	// compute light
	float light = ambient_light + specular_light + diffuse_light;

	// send color to fragment shader
	color = object_color * light;

	// compute gl_Position
	float x = v_position.x;
	float y = v_position.y;
	float z = v_position.z;

	float new_radius = mod(x * y * z, 1);
	float new_speed = mod(x * mod(y * z, 1), 1);

	x += new_radius * cos(new_speed * time);
	y += new_radius * sin(new_speed * time);

	gl_Position = Projection * View * Model * vec4(vec3(x, y, z), 1);
}
