#version 420


in vec2 FStexCoord;

uniform sampler2D texture2D;

out vec4 fragColor;


void main()
{	
	fragColor = texture(texture2D, FStexCoord);
}