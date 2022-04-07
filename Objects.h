#ifndef OBJECTS_H
#define OBJECTS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <vector>

#include <stdlib.h>     /* srand, rand */
#include <time.h>

using namespace std;

vector<glm::vec2> controlPoints4 = {
    glm::vec2(-1.0f, -1.0f),
    glm::vec2(-1.0f, 1.0f),
    glm::vec2(1.0f, -1.0f),
    glm::vec2(1.0f, 1.0f)
};

vector<glm::vec2> controlPoints8 = {
	glm::vec2(-2.0f, 0.0f),
	glm::vec2(-1.5f, 0.5f),
	glm::vec2(-1.25, -2.0f),
	glm::vec2(-1.0f, 0.0f),
    glm::vec2(-1.0f, -1.0f),
    glm::vec2(-1.0f, 1.0f),
    glm::vec2(1.0f, -1.0f),
    glm::vec2(1.0f, 1.0f)
};

vector<glm::vec3> controlPoints8_3D = {
    glm::vec3(-2.0f, 0.0f, 1.0f),
    glm::vec3(-1.5f, 0.5f, 0.5f),
    glm::vec3(-1.25, -2.0f, 0.0f),
    glm::vec3(-1.0f, 0.0f, -0.5f),
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f, 1.0f, -1.5f),
    glm::vec3(1.0f, -1.0f, -1.0f),
    glm::vec3(1.0f, 1.0f, 0.0f)
};

vector<glm::vec3> randomPointsCurve() {
	vector<glm::vec3> points;
	srand(time(NULL));
	for (int i = 0; i < 6; i++) {
		float x = (float)(i - 3);
		float y = (float)((rand() % 2) - 1);
		float z = (float)(rand() % 3);
		points.push_back(glm::vec3(x, y, z));
	}
	return points;
}


// generates a vector of vector glm::vec3 with x rows and y columns to compute bezier surface
vector<vector<glm::vec3>> randomPointsSurface(float x, float y) {
	vector<vector<glm::vec3>> control;
	vector<glm::vec3> row;
	for (float i = -x/2.0f; i < x/2.0f; i++) {
		for (float j = -y/2.0f; j < y/2.0f; j++) {
			float x = i;
			float y = j;
			float z = (float)((rand() % 100)%4 - 2);
			row.push_back(glm::vec3(x, y, z));
		}
        control.push_back(row);
		row.clear();
	}
	return control;
}


#endif // !OBJECTS_H
