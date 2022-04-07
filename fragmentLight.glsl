#version 330 core

in vec3 color;

out vec4 FragColor;

uniform vec3 cameraPosition;

void main(){
	FragColor = vec4(color, 0.0f);
}