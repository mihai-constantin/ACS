#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform sampler2D heightMap;
uniform sampler2D earthTexture;

uniform vec2 heightMapSize;

out vec2 texcoord;

// Uniforms for light properties
uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;

// Output value to fragment shader
out vec3 color;

void main()
{
	// pass v_texture_coord as output to Fragment Shader
	texcoord = v_texture_coord;

	vec3 new_v_position = v_position;
	new_v_position.y = texture2D(heightMap, v_texture_coord).r * 7.5f;

	vec2 texelSize = vec2(1.0/heightMapSize.x, 1.0/heightMapSize.y);
	float heightRight =  texture2D(heightMap, vec2(v_texture_coord.x + texelSize.x, v_texture_coord.y)).r;
	float heightUp = texture2D(heightMap, vec2(v_texture_coord.x, v_texture_coord.y + texelSize.y)).r;

	float H_x = new_v_position.y - heightRight;
	float H_y = new_v_position.y - heightUp;

	H_x = 50.f * H_x;
	H_y = 50.f * H_y;

	vec3 normal = normalize(vec3(H_x, 1, H_y));

	// compute world space vectors
	vec3 world_pos = (Model * vec4(new_v_position, 1)).xyz;
	vec3 world_normal = normalize( mat3(Model) * normalize(normal));

	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_pos);
	vec3 V = normalize(eye_position - world_pos);
	vec3 H = normalize(L + V);

	// TODO: define ambient light component
	float ambient_light = 0.25;

	// TODO: compute diffuse light component
	float diffuse_light = material_kd * max (dot(N, L), 0);

	// TODO: compute specular light component
	float specular_light = 0;

	if (diffuse_light > 0)
	{
		specular_light = material_ks * pow(max(dot(normalize(N), H), 0), material_shininess);
	}

	// TODO: compute light
	float light = ambient_light + specular_light + diffuse_light;

	// TODO: send color light output to fragment shader
	color = object_color * light;

	gl_Position = Projection * View * Model * vec4(new_v_position, 1.0);
}
