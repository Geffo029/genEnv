#version 420


in layout(location=0) vec3 position;
in layout(location=1) vec2 VStexCoord;

uniform mat4 MVPMatrix;

out vec2 FStexCoord;


void main()
{
    gl_Position = MVPMatrix * vec4(position, 1.0);
    FStexCoord = VStexCoord;
}