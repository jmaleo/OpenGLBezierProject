#pragma once
#ifndef NORMALMESH_H
#define NORMALMESH_H

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

class NormalMesh {
public:
    // mesh data
    vector <glm::vec3> vertices;
    vector <glm::vec3> normals;
    vector <unsigned int> indices;
    vector<glm::vec3> lightsPos;
    vector<glm::vec3> lightsColor;
    unsigned int VAO;
    Camera* camera;
    bool showNormalAsColor = true;

    NormalMesh(vector<glm::vec3> vertices,vector<glm::vec3> normals,Camera* cam)
    {
        this->showNormalAsColor = false;
        this->vertices = createLines(vertices, normals);
        this->normals = normals;
        this->camera = cam;
    }

    NormalMesh(vector<glm::vec3> vertices, vector<unsigned int> indices, vector<glm::vec3> normals, vector<glm::vec3> lights, Camera* cam)
    {
        this->showNormalAsColor = true;
        this->lightsPos = getLightPosition(lights);
        this->lightsColor = getLightColor(lights);
        this->indices = indices;
        this->vertices = vertices;
        this->normals = normals;
        this->camera = cam;
    }

    void setVerticesAndNormals(vector<glm::vec3> vertices, vector<glm::vec3> normals) {
        this->vertices = vertices;
        this->normals = normals;
        this->vertices = createLines(vertices, normals);
        setupMesh();
    }
	
    void setVerticesAndNormals(vector<glm::vec3> vertices,vector<unsigned int> indices, vector<glm::vec3> normals) {
        this->vertices = vertices;
        this->normals = normals;
        this->indices = indices;
        setupMesh();
    }	


    // Calls before main loop
    void setupMesh()
    {

        glGenBuffers(1, &EBO);
        glGenBuffers(1, &VBO1);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        //vertex position
        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		
        if (showNormalAsColor) {
            glGenBuffers(1, &VBO2);
            //color
            glBindBuffer(GL_ARRAY_BUFFER, VBO2);
            glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                &indices[0], GL_STATIC_DRAW);
        }

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

		

        // compute Lights
		
        // draw mesh
        glLineWidth(1);
        glBindVertexArray(VAO);
        if (showNormalAsColor) {
            computeLights(shader);
            glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
        }
        else {
            glDrawArrays(GL_LINES, 0, (GLsizei)vertices.size());
        }
		
        glBindVertexArray(0);
    }
private:
    //  render data
    unsigned int VBO1,VBO2, EBO;


    void computeLights(ShaderProgram* shader) {
        for (int i = 0; i < lightsColor.size(); i++) {
            string lightPos = "lightPos[" + to_string(i) + "]";
            string lightColor = "lightColor[" + to_string(i) + "]";
            shader->setVec3(lightPos, this->lightsPos.at(i));
            shader->setVec3(lightColor, this->lightsColor.at(i));
        }
    }

    vector<glm::vec3> createLines(vector<glm::vec3> vertices, vector<glm::vec3> normals) {
        vector<glm::vec3> lines;
        for (int i = 0; i < vertices.size(); i++) {
            lines.push_back(vertices.at(i));
            lines.push_back(vertices.at(i)+ (normals.at(i) * 0.1f));
        }
        return lines;
    }
    vector<glm::vec3> getLightColor(vector<glm::vec3> lights) {
        vector<glm::vec3> col;
        for (int i = 1; i < lights.size(); i += 2) {
            col.push_back(lights.at(i));
        }
        return col;
    }
    vector<glm::vec3> getLightPosition(vector<glm::vec3> lights) {
        vector<glm::vec3> pos;
        for (int i = 0; i < lights.size(); i += 2) {
            pos.push_back(lights.at(i));
        }
        return pos;
    }

};
#endif