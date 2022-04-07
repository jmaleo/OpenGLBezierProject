#version 330 core

in vec3 position;
in vec3 normal;

out vec4 FragColor;


uniform vec3 cameraPosition;

void main(){
	FragColor = vec4(abs(position)*0.5f + 0.5f, 0.0f);
}