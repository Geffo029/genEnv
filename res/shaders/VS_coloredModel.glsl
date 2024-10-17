#version 420



in layout(location=0) vec3 position;
uniform mat4 MVPMatrix;


void main()
{
    gl_Position = MVPMatrix * vec4(position, 1.0);
}