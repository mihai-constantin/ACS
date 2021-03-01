#version 330

// get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform bool spot_light_activated;
uniform float cut_off_angle;

uniform vec3 object_color;

layout(location = 0) out vec4 out_color;

void main()
{
	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	
	// define ambient light component
	float ambient_light = 0.25;

	// compute diffuse light component
	float diffuse_light = material_kd * max (dot(N, L), 0);

	// compute specular light component
	float specular_light = 0;

	if (diffuse_light > 0) {
		specular_light = material_ks * pow(max(dot(normalize(N), H), 0), material_shininess);
	}

	// compute light
	float light = ambient_light + specular_light + diffuse_light;

	// write pixel out color
	float cut_off = radians(cut_off_angle);
	float spot_light = dot(-L, light_direction);
	float spot_light_limit = cos(cut_off);
	float computed_light= 0;
	float factor_de_atenuare = (1 / pow(distance(light_position, world_position), 2));
	
	if (spot_light_activated) {
		if (spot_light > cos(cut_off)) {
			// fragmentul este iluminat de spot, deci se calculeaza valoarea luminii conform  modelului Phong
			// se calculeaza atenuarea luminii
			// Quadratic attenuation
			float linear_att = (spot_light - spot_light_limit) / (1 - spot_light_limit);
			float light_att_factor = pow(linear_att, 2);
			factor_de_atenuare = light_att_factor;
			computed_light = ambient_light + factor_de_atenuare * ( diffuse_light + specular_light);
		} else {
			computed_light = ambient_light;
		}
	} else {
		//computed_light = ambient_light + factor_de_atenuare * ( diffuse_light + specular_light);
		computed_light=1;
	}

	vec3 color = computed_light * object_color * light;
	out_color = vec4(color,1);
}