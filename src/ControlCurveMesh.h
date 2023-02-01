#pragma once
#ifndef CONTROLCURVEMESH_H
#define CONTROLCURVEMESH_H

#pragma once

// #include <Windows.h>

#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "ShaderProgram.h"
#include "Camera.h"

using namespace std;

class ControlCurveMesh {
public:
    // mesh data
    vector <glm::vec3> vertices;
    unsigned int VAO;
    Camera* camera;

    ControlCurveMesh(vector<glm::vec3> vertices, Camera* cam)
    {
        this->vertices = vertices;
        this->camera = cam;
    }
	
    ControlCurveMesh(vector<glm::vec2> vertices, Camera* cam)
    {
        this->vertices = addZaxis(vertices);
        this->camera = cam;
    }

    void setControlPoints(vector<glm::vec3> vertices) {
		this->vertices = vertices;
        setupMesh();
    }

    void setControlPoints(vector<glm::vec2> vertices) {
		this->vertices = addZaxis(vertices);
        setupMesh();
    }

    // Calls before main loop
    void setupMesh()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

        // vertex positions

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        glBindVertexArray(0);
    }

    // Calls after settings for camera
    void draw(ShaderProgram* shader, float width, float height)
    {
        shader->use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), width / height, 0.1f, 100.0f);
        shader->setMat4("projection", projection);

        shader->setVec3("cameraPosition", camera->Position);

        // camera/view transformation
        glm::mat4 view = camera->GetViewMatrix();
        shader->setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        shader->setMat4("model", model);

        // draw mesh
        glLineWidth(1);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_STRIP, 0, (GLsizei)vertices.size());
        glBindVertexArray(0);
    }
private:
    //  render data
    unsigned int VBO, EBO;

    vector<glm::vec3> addZaxis(vector<glm::vec2> points) {
        vector<glm::vec3> points3 = vector<glm::vec3>();
        for (int i = 0; i < points.size(); i++) {

            points3.push_back(glm::vec3(points[i].x, points[i].y, 0.0f));
        }
        return points3;
    }

};
#endif