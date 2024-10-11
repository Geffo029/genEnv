#version 420


in layout(location=0) vec3 position;
in layout(location=1) vec4 color;

uniform mat4 MVPMatrix;

out vec4 vertexColor;


void main() {
	
	gl_Position = MVPMatrix * vec4(position, 1.0);
	//gl_Position = vec4(position, 1.0);
	vertexColor = color;
}