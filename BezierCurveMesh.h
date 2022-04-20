#ifndef BEZIERCURVEMESH_H
#define BEZIERCURVEMESH_H

#include <Windows.h>

#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "ShaderProgram.h"
#include "Camera.h"

using namespace std;

class BezierCurveMesh {
public:
    // mesh data
    vector <glm::vec3> vertices;
    vector <unsigned int> indices;
    unsigned int VAO;
    Camera* camera;

    BezierCurveMesh(vector<glm::vec3> vertices, vector<unsigned int> indices, Camera* cam)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->camera = cam;
    }

    void setVertices(vector<glm::vec3> vertices) {
        this->vertices = vertices;
    }

    void setIndices(vector<unsigned int> indices) {
        this->indices = indices;
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
        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), width/height, 0.1f, 100.0f);
        shader->setMat4("projection", projection);
        shader->setVec3("cameraPosition", camera->Position);
        // camera/view transformation
        glm::mat4 view = camera->GetViewMatrix();
        shader->setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        shader->setMat4("model", model);
		
        // draw mesh
        glLineWidth(10);
        glBindVertexArray(VAO);
        glDrawElements(GL_LINE_STRIP, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
private:
    //  render data
    unsigned int VBO, EBO;

};
#endif