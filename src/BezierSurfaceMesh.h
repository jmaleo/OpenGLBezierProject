#ifndef BEZIERSURFACEMESH_H
#define BEZIERSURFACEMESH_H

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

class BezierSurfaceMesh {
public:
    // mesh data
    vector <glm::vec3> vertices;
    vector<unsigned int> indices;
    vector <glm::vec3> normales;
    vector<glm::vec3> lightsPos;
    vector<glm::vec3> lightsColor;
    glm::vec3 surfaceColor;
    unsigned int VAO;
    Camera* camera;

    BezierSurfaceMesh(vector<vector<glm::vec3>> vertices, glm::vec3 surfaceColor, vector<glm::vec3> lights, Camera* cam)
    {   
        for (int i = 0; i < vertices.size(); i++) {
			for (int j = 0; j < vertices[i].size(); j++) {
				this->vertices.push_back(vertices.at(i).at(j));
			}
        }
        this->lightsPos = getLightPosition(lights);
        this->lightsColor = getLightColor(lights); 
        this->surfaceColor = surfaceColor;
        this->indices = arrayToTriangles(vertices);
        this->normales = computeNormalofPoints();
        this->camera = cam;
    }

    vector<glm::vec3> getVertices() {
		return this->vertices;
    }
	
    vector<glm::vec3> getNormales() {
		return this->normales;
    }

    vector<unsigned int> getIndices() {
		return this->indices;
    }

    vector <glm::vec3> getLightsPos() {
		return this->lightsPos;
	}
	
    vector <glm::vec3> getLightsColor() {
		return this->lightsColor;
	}

    void setVertices(vector<vector<glm::vec3>> vertices) {
        this->vertices.clear();
        for (int i = 0; i < vertices.size(); i++) {
            for (int j = 0; j < vertices[i].size(); j++) {
                this->vertices.push_back(vertices.at(i).at(j));
            }
        }
        this->normales = computeNormalofPoints();
        setupMesh();
    }

    // Calls before main loop
    void setupMesh()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO1);
        glGenBuffers(1, &VBO2);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        // vertex positions
        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
		
        // vertex normals
        glBindBuffer(GL_ARRAY_BUFFER, VBO2);
        glBufferData(GL_ARRAY_BUFFER, normales.size() * sizeof(glm::vec3), &normales[0], GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
            &indices[0], GL_STATIC_DRAW);

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
		
        shader->setVec3("objectColor", this->surfaceColor);
		
		// compute Lights
        computeLights(shader);

        // draw mesh
        glLineWidth(1);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
	


private:
    //  render data
    unsigned int VBO1, VBO2, EBO;

	
    void computeLights(ShaderProgram* shader) {
        for (int i = 0; i < lightsColor.size(); i++) {
            string lightPos = "lightPos[" + to_string(i) + "]";
			string lightColor = "lightColor[" + to_string(i) + "]";
			shader->setVec3(lightPos, this->lightsPos.at(i));
			shader->setVec3(lightColor, this->lightsColor.at(i));
        }
    }
	
	// Computes the normal of the triangle
    glm::vec3 getNormalofTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {
        glm::vec3 v12 = v2 - v1;
        glm::vec3 v13 = v3 - v1;
        glm::vec3 normal = glm::normalize(glm::cross(v12, v13));
        return normal;
    }
	

    vector<glm::vec3> computeNormalofPoints() {
        vector<glm::vec3> normales = vector<glm::vec3>(vertices.size(), glm::vec3(0.0f, 0.0f, 0.0f));
		////vector with indices.size() 0
        vector<int> nbNormales = vector<int>(vertices.size(), 0);
		for (int i = 0; i < indices.size(); i += 3) {
			glm::vec3 v1 = vertices.at(indices.at(i));
			glm::vec3 v2 = vertices.at(indices.at(i + 1));
			glm::vec3 v3 = vertices.at(indices.at(i + 2));
			
			glm::vec3 normal = getNormalofTriangle(v1, v2, v3);
			
			normales.at(indices.at(i)) = normal;
            normales.at(indices.at(i + 1)) = normal;
            normales.at(indices.at(i + 2)) = normal;

			for (int j = 0; j < 3; j++)
				nbNormales.at(indices.at(i + j))++;
            
		}
        for (int i = 0; i < normales.size(); i++) {
            normales.at(i) /= nbNormales.at(i);
            normales.at(i) = glm::normalize(normales.at(i));
        }
		return normales;
    }

    vector<unsigned int> arrayToTriangles(vector<vector<glm::vec3>> matrix) {
        vector<unsigned int> indices;
        size_t n = matrix.size();
        size_t m = matrix[0].size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < m - 1; j++) {
                indices.push_back((unsigned int)(i * m + j + 1));				
                indices.push_back((unsigned int)(i * m + j));
                indices.push_back((unsigned int)((i + 1) * m + j + 1));
				
                indices.push_back((unsigned int)((i + 1) * m + j));
                indices.push_back((unsigned int)((i + 1) * m + j + 1));
                indices.push_back((unsigned int)(i * m + j));
            }
        }
        return indices;
    }

    vector<glm::vec3> getLightColor(vector<glm::vec3> lights) {
        vector<glm::vec3> col;
        for (int i = 1; i < lights.size(); i += 2){
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