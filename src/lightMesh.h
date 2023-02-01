#pragma once
#ifndef LIGHTMESH_H
#define LIGHTMESH_H

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

class LightMesh {
public:
    // mesh data
    vector <glm::vec3> lightsPos;
    vector <glm::vec3> lightsCol;
    vector <unsigned int> indices;
    unsigned int VAO;
    Camera* camera;

    LightMesh(vector<glm::vec3> lightsPos, vector<glm::vec3> lightsCol, Camera* cam)
    {
        this->lightsPos = lightsPos;
        this->lightsCol = lightsCol;
        for (int i = 0; i < this->lightsPos.size(); i++)
            indices.push_back(i);
        this->camera = cam;
    }

    // Calls before main loop
    void setupMesh()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO1);
        glGenBuffers(1, &VBO2);

        glBindVertexArray(VAO);
		
        //VertexPosition
        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, lightsPos.size() * sizeof(glm::vec3), &lightsPos[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //VertexColor
        glBindBuffer(GL_ARRAY_BUFFER, VBO2);
        glBufferData(GL_ARRAY_BUFFER, lightsCol.size() * sizeof(glm::vec3), &lightsCol[0], GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);

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
        glPointSize(10);
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, (GLsizei)lightsPos.size());
        glBindVertexArray(0);
    }
private:
    //  render data
    unsigned int VBO1, VBO2, EBO;

};
#endif