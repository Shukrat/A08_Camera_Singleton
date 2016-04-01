#version 430

in vec4 vertColor;
uniform vec4 color;

void main(){
     gl_FragColor = color * vertColor;
}