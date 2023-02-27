#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <memory>
#include <math.h>

#include "Object.t.hpp"
#include "Scene.t.hpp"
#include "Camera.h"
#include "ParticlesContainer.t.hpp"


float initial_time = clock ();

float timeExec() {
  return (clock() - initial_time) / CLOCKS_PER_SEC * 1000;
}

Scene<glm::vec3>* generateCubeScene (Camera* cam);

/**
 * @brief 
 * 
 * @param id
 * @param position Position of the top left front cube.
 * @param length length of one edge of the cube.
 * @param colors Unique color for the entire cube.
 * @param normal_dir Direction of the normal (interior => false       exterior => true)
 * @return Object<glm::vec3> 
 */
Object<glm::vec3>* generateCube (int id, glm::vec3 position, float length, glm::vec3 col, bool normal_dir);

/**
 * @brief Generates cube (or rectangular shape)
 * 
 * @param position of the top left back vertex;
 * @param length1 
 * @param length2 
 * @return std::vector<glm::vec3> 
 */
std::vector<glm::vec3> generateCubeVertices(glm::vec3 position, float length1, float length2);

/**
 * @brief Generates Indices of the prism or cube.
 * 
 * @param vertices 
 * @return std::vector<int> 
 */
std::vector<unsigned int> generateCubeIndices ();

/**
 * @brief Generates normales of given vertices, for a cube of prism.
 * 
 * @param vertices 
 * @return std::vector <glm::vec3> 
 */
std::vector <glm::vec3> generateCubeNormales (std::vector <glm::vec3> vertices, bool normal_dir);

std::vector < Object<glm::vec3> * > create_grid_objects (Object<glm::vec3>*, float size);