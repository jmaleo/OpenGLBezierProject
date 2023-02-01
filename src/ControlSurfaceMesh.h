#pragma once
#ifndef CONTROLSURFACEMESH_H
#define CONTROLSURFACEMESH_H

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

class ControlSurfaceMesh {
public:
    // mesh data
    vector <glm::vec3> vertices;
    vector<unsigned int> indices;
    unsigned int VAO;
    Camera* camera;

    ControlSurfaceMesh(vector<vector<glm::vec3>> vertices, Camera* cam)
    {
        for (int i = 0; i < vertices.size(); i++) {
			for (int j = 0; j < vertices[i].size(); j++) {
				this->vertices.push_back(vertices[i][j]);
			}
        }
        this->indices = lineIndices(vertices);
        this->camera = cam;
    }

    void setVertices(vector<vector<glm::vec3>> vertices)
    {
		this->vertices.clear();
        for (int i = 0; i < vertices.size(); i++) {
            for (int j = 0; j < vertices[i].size(); j++) {
                this->vertices.push_back(vertices[i][j]);
            }
        }
        this->indices = lineIndices(vertices);
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
		
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
            &indices[0], GL_STATIC_DRAW);

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
        glPointSize(10);
        glBindVertexArray(VAO);
		
        glDrawElements(GL_LINES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

        //glDrawArrays(GL_LINE_STRIP, 0, (GLsizei)vertices.size());
        glBindVertexArray(0);
    }
private:
    //  render data
    unsigned int VBO, EBO;

    vector<unsigned int> lineIndices(vector<vector<glm::vec3>> matrix) {
		vector<unsigned int> indices;
        int x = (int)matrix.size();
        int y = (int)matrix[0].size();
		for (int i = 0; i < x - 1; i++) {
            for (int j = 0; j < y - 1; j++) {
                indices.push_back(i * y + j);
                indices.push_back(i * y + j + 1);
                indices.push_back(i * y + j);
                indices.push_back((i + 1) * y + j);
            }
            indices.push_back(i * y + y - 1);
            indices.push_back((i + 1) * y + y - 1);
		}
        for (int j = 0; j < matrix[x - 1].size()-1; j++) {
            indices.push_back((x-1) * y + j);
            indices.push_back((x - 1) * y + j + 1);
        }
			
		return indices;
    }
		
    vector<glm::vec3> addZaxis(vector<glm::vec2> points) {
        vector<glm::vec3> points3 = vector<glm::vec3>();
        for (int i = 0; i < points.size(); i++) {

            points3.push_back(glm::vec3(points[i].x, points[i].y, 0.0f));
        }
        return points3;
    }

};
#endif