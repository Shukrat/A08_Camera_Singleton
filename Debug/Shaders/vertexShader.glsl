#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
uniform mat4 worldMatrix;
out vec4 vertColor;

void main(){
     gl_Position = worldMatrix * vec4(position, 1);
	vertColor = vec4(color, 1);
}