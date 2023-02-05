#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include "Object.t.hpp"
#include "Scene.t.hpp"

/**
 * @brief 
 * TODO
 * 
 * @param nb_cubes 
 * @param nb_lights 
 * @return MyObject<glm::vec3> 
 */
Scene<glm::vec3> generateCubeScene (glm::vec3 position_min, glm::vec3 position_max, int nb_cubes, int nb_lights);


/**
 * @brief 
 * TODO
 * 
 * @param nb_sphere 
 * @param nb_lights 
 * @return MyObject<glm::vec3> 
 */
Scene<glm::vec3> generateSphereScene (glm::vec3 position_min, glm::vec3 position_max, int nb_sphere, int nb_lights);

/**
 * @brief 
 * 
 * @param position_max Position of the top left front cube.
 * @param position_min Position of the bottom right back cube. 
 * @param colors Unique color for the entire cube.
 * @param normal_dir Direction of the normal (interior => false       exterior => true)
 * @return MyObject<glm::vec3> 
 */
MyObject<glm::vec3> generateCube (glm::vec3 position_max, glm::vec3 position_min, glm::vec4 col, bool normal_dir);

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
std::vector<int> generateCubeIndices ();

/**
 * @brief Generates normales of given vertices, for a cube of prism.
 * 
 * @param vertices 
 * @return std::vector <glm::vec3> 
 */
std::vector <glm::vec3> generateCubeNormales (std::vector <glm::vec3> vertices, bool normal_dir);

/**
 * @brief 
 * 
 * @param position Position of the sphere.
 * @param radius Radius of the Sphere
 * @param colors Unique color for the entire sphere
 * @param normal_dir Direction of the normal (interior => false       exterior => true)
 * @return MyObject<glm::vec3> 
 */
MyObject<glm::vec3> generateSphere (glm::vec3 position, float radius, glm::vec4 col, bool normal_dir);


/**
 * @brief Generates a vector containing nb_elem of the same value (color).
 * 
 * @param col 
 * @param nb_elem 
 * @return std::vector<glm::vec4> 
 */
std::vector<glm::vec4> generateColors (glm::vec4 col, int nb_elem);