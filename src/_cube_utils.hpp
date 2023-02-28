#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>

/**
 * @brief Generates a cube (or a rectangular shape).
 * 
 * @param position of the top left front vertex
 * @param length1 
 * @param length2 
 * @return std::vector<glm::vec3> 
 */
std::vector<glm::vec3> generateCubeVertices(glm::vec3 position, float length1, float length2){

    std::vector<glm::vec3> vertices;

    // if the origin and positions are like that : 
    //                                                     0 -------4
    //     |                                               /|      /|
    //     |                                              /_|3____/ |7
    //    O ----->                       here :          1|/     5|/ 
    //      \                                            2/_______/6
    //       \                                          
    ////////////////////////////////////////////////
    
    // vertices.push_back(position); // 0 
    // vertices.push_back(glm::vec3(position[0], position[1], position[2]+length1)); //  1 
    // vertices.push_back(glm::vec3(position[0], position[1]-length1, position[2]+length1)); // 2 
    // vertices.push_back(glm::vec3(position[0], position[1]-length1, position[2])); // 3 
    // vertices.push_back(glm::vec3(position[0]+length2, position[1], position[2])); // 4 
    // vertices.push_back(glm::vec3(position[0]+length2, position[1], position[2]+length1)); // 5 
    // vertices.push_back(glm::vec3(position[0]+length2, position[1]-length1, position[2]+length1)); // 6 
    // vertices.push_back(glm::vec3(position[0]+length2, position[1]-length1, position[2])); // 7 

    // left face
    vertices.push_back(position); // 0 
    vertices.push_back(glm::vec3(position[0], position[1], position[2]+length1)); //  1 
    vertices.push_back(glm::vec3(position[0], position[1]-length1, position[2]+length1)); // 2 
    vertices.push_back(glm::vec3(position[0], position[1]-length1, position[2])); // 3 

    // right face 
    vertices.push_back(glm::vec3(position[0]+length2, position[1], position[2])); // 4 
    vertices.push_back(glm::vec3(position[0]+length2, position[1], position[2]+length1)); // 5 
    vertices.push_back(glm::vec3(position[0]+length2, position[1]-length1, position[2]+length1)); // 6 
    vertices.push_back(glm::vec3(position[0]+length2, position[1]-length1, position[2])); // 7

    // upper face
    vertices.push_back(position); // 0 
    vertices.push_back(glm::vec3(position[0]+length2, position[1], position[2])); // 4 
    vertices.push_back(glm::vec3(position[0]+length2, position[1], position[2]+length1)); // 5 
    vertices.push_back(glm::vec3(position[0], position[1], position[2]+length1)); //  1 

    // botton face
    vertices.push_back(glm::vec3(position[0], position[1]-length1, position[2])); // 3 
    vertices.push_back(glm::vec3(position[0]+length2, position[1]-length1, position[2])); // 7 
    vertices.push_back(glm::vec3(position[0]+length2, position[1]-length1, position[2]+length1)); // 6 
    vertices.push_back(glm::vec3(position[0], position[1]-length1, position[2]+length1)); // 2 

    // front face
    vertices.push_back(glm::vec3(position[0], position[1], position[2]+length1)); //  1 
    vertices.push_back(glm::vec3(position[0], position[1]-length1, position[2]+length1)); // 2 
    vertices.push_back(glm::vec3(position[0]+length2, position[1]-length1, position[2]+length1)); // 6
    vertices.push_back(glm::vec3(position[0]+length2, position[1], position[2]+length1)); // 5 

    // back face
    vertices.push_back(position); // 0 
    vertices.push_back(glm::vec3(position[0], position[1]-length1, position[2])); // 3 
    vertices.push_back(glm::vec3(position[0]+length2, position[1]-length1, position[2])); // 7 
    vertices.push_back(glm::vec3(position[0]+length2, position[1], position[2])); // 4 

    return vertices;
}


/**
 * @brief Generates normales of given vertices, for a cube of prism.
 * 
 * @return std::vector <glm::vec3> 
 */
std::vector <glm::vec3> generateCubeNormales (bool normal_dir){
    std::vector<glm::vec3> normales;
    float dir = (normal_dir)?1.0f:-1.0f;
    for (int i = 0; i < 4; i++){
        normales.push_back(dir * glm::vec3(-1.0f, 0.0f, 0.0f)); // Left face
    }
    for (int i = 0; i < 4; i++){
        normales.push_back(dir * glm::vec3(1.0f, 0.0f, 0.0f)); // Right face
    }
    for (int i = 0; i < 4; i++){
        normales.push_back(dir * glm::vec3(0.0f, 1.0f, 0.0f)); // upper face
    }
    for (int i = 0; i < 4; i++){
        normales.push_back(dir * glm::vec3(0.0f, -1.0f, 0.0f)); // bottom face
    }
    for (int i = 0; i < 4; i++){
        normales.push_back(dir * glm::vec3(0.0f, 0.0f, 1.0f)); // front face
    }
    for (int i = 0; i < 4; i++){
        normales.push_back(dir * glm::vec3(0.0f, 0.0f, -1.0f)); // back face
    }
    return normales;
}

/**
 * @brief Generates Indices of the prism or cube.
 * 
 * @param vertices 
 * @return std::vector<int> 
 */
std::vector<unsigned int> generateCubeIndices (){
    std::vector<unsigned int> indices;

    for (int i = 0; i < 6; i++){
        int idx = i * 4;
        indices.push_back(idx);
        indices.push_back(idx+1);
        indices.push_back(idx+2);
        indices.push_back(idx+2);
        indices.push_back(idx+3);
        indices.push_back(idx);
    }
    return indices;
}


std::vector <glm::vec3> generateSphereVertices (glm::vec3 center, float radius, int stacks, int slices){
    std::vector<glm::vec3> vertices;
    // calculate vertices
    for (int i = 0; i <= stacks; ++i) {
        float phi = glm::pi<float>() * static_cast<float>(i) / static_cast<float>(stacks);
        for (int j = 0; j <= slices; ++j) {
            float theta = 2 * glm::pi<float>() * static_cast<float>(j) / static_cast<float>(slices);
            float x = center.x + radius * glm::sin(phi) * glm::cos(theta);
            float y = center.y + radius * glm::sin(phi) * glm::sin(theta);
            float z = center.z + radius * glm::cos(phi);
            vertices.push_back(glm::vec3(x, y, z));
        }
    }
    return vertices;
}

std::vector <unsigned int> generateSphereIndices (float stacks, float slices){
    std::vector<unsigned int> indices;
    // calculate indices
    for (int i = 0; i < stacks; ++i) {
        for (int j = 0; j < slices; ++j) {
            unsigned int first = (i * (slices + 1)) + j;
            unsigned int second = first + slices + 1;
            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }
    return indices;
}

std::vector <glm::vec3> generateSphereNormales (glm::vec3 center, std::vector <glm::vec3> vertices){
    std::vector<glm::vec3> normales;
    for (int i = 0; i < vertices.size(); i++){
        normales.push_back(glm::normalize(vertices[i] - center));
    }
    return normales;
}