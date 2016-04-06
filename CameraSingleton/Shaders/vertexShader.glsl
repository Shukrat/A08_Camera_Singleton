#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 inColor;
uniform mat4 worldMatrix;
out vec4 vertColor;

void main(){
     gl_Position = worldMatrix * vec4(position, 1);
	vertColor = vec4(1, 1, 1, 1);
}