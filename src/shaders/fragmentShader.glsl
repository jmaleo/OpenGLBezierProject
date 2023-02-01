#version 330 core

in vec3 position;
in vec3 normal;

out vec4 FragColor;


uniform vec3 cameraPosition;
uniform vec3 objectColor;


uniform vec3 lightPos[3];
uniform vec3 lightColor[3];

float ambientStrength = 0.1;

float diffuse(vec3 normal, vec3 lightDir) {
    return max(dot(normal, lightDir), 0.0) * 0.5;
}

float specular(vec3 normal, vec3 lightPos, vec3 eyeView){
    vec3 lightDir = normalize(position - lightPos);
    vec3 viewDir  = normalize(eyeView - position);
    vec3 reflectDir = reflect(lightDir, normal);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0), 64);
    return spec * 0.8;
}

void main(){
    vec3 result = vec3(0.0f);
    vec3 norm = -normalize(normal);

    //ambient
    for(int i = 0; i < 3; i++){
        vec3 ambient = ambientStrength * lightColor[i];
        vec3 temp = ambient;
        temp += ambient;
        temp += diffuse(norm, normalize(position - lightPos[i])) * lightColor[i];
        temp += specular(norm, lightPos[i], cameraPosition) * lightColor[i];
		temp *= objectColor;
		result += temp;
	}

    FragColor = vec4(result, 1.0f);
}