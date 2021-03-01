#version 330
 
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform float elapsedTime;
 
in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	// calculate the out_color using the texture2D() function
	vec4 color_texture_1 = texture2D(texture_1, texcoord);
	vec4 color_texture_2 = texture2D(texture_2, texcoord);

	vec2 newCoord = texcoord;
	newCoord.x += elapsedTime / 10;
	vec4 color = texture2D(texture_1, newCoord);

	if(color_texture_1.a < 0.5f)
		discard;

	// color = mix(color_texture_1, color_texture_2, 0.5f);

	out_color = color;
}