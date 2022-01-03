#version 330
 
uniform sampler2D heightMap;
uniform sampler2D earthTexture;
 
in vec2 texcoord;
in vec3 color;

layout(location = 0) out vec4 out_color;

void main()
{
	vec4 color_texture_1 = texture2D(heightMap, texcoord);
	vec4 color_texture_2 = texture2D(earthTexture, texcoord);

	// calculate the out_color using the texture2D() function
	// vec4 color_texture_1 = texture2D(texture_1, texcoord);

	//if(color_texture_1.a < 0.5f)
		// discard;

	// out_color = vec4(color, 1);
	out_color = color_texture_2;
}