#ifndef LIGHTS_H
#define LIGHTS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <vector>

#include <stdlib.h>     /* srand, rand */
#include <time.h>

using namespace std;


glm::vec3 light1Pos = glm::vec3(-4.5f, 0.0f, 10.0f);
glm::vec3 light2Pos = glm::vec3(5.0f, 0.0f, 10.0f);


glm::vec3 light1Col = glm::vec3(1.0f, 0.6f, 0.4f) * 0.7f;
glm::vec3 light2Col = glm::vec3(0.0f, 0.6f, 1.0f) * 0.4f;


glm::vec3 light3pos = glm::vec3(-5.0f, 0.0f, -10.0f);
glm::vec3 light3col = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;

vector<glm::vec3> lightsVector3() {
	vector<glm::vec3> lightsVector;
	lightsVector.push_back(light3pos);
	lightsVector.push_back(light3col);
	lightsVector.push_back(light2Pos);
	lightsVector.push_back(light2Col);
	lightsVector.push_back(light1Pos);
	lightsVector.push_back(light1Col);
	return lightsVector;
}


#endif