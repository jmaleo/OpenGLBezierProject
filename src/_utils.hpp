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

#include "Object.t.hpp"
#include "Particle.t.hpp"
#include "Scene.t.hpp"
#include "Camera.h"

float initial_time = clock ();

float timeExec() {
  return (clock() - initial_time) / CLOCKS_PER_SEC * 1000;
}

Scene<glm::vec3>* generateCubeScene (Camera* cam);

/**
 * @brief 
 * TODO
 * 
 * @param nb_cubes 
 * @param nb_lights 
 * @return MyObject<glm::vec3> 
 */
Scene<glm::vec3>* generateRandomCubeScene (Camera* cam, glm::vec3 position, float length, int nb_cubes, int nb_lights);

/**
 * @brief 
 * TODO
 * 
 * @param nb_sphere 
 * @param nb_lights 
 * @return MyObject<glm::vec3> 
 */
Scene<glm::vec3>* generateSphereScene (glm::vec3 position_min, glm::vec3 position_max, int nb_sphere, int nb_lights);

/**
 * @brief 
 * 
 * @param id
 * @param position Position of the top left front cube.
 * @param length length of one edge of the cube.
 * @param colors Unique color for the entire cube.
 * @param normal_dir Direction of the normal (interior => false       exterior => true)
 * @return MyObject<glm::vec3> 
 */
MyObject<glm::vec3>* generateCube (int id, glm::vec3 position, float length, glm::vec3 col, bool normal_dir);

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

/**
 * @brief 
 * 
 * @param id
 * @param position Position of the sphere.
 * @param radius Radius of the Sphere
 * @param colors Unique color for the entire sphere
 * @param normal_dir Direction of the normal (interior => false       exterior => true)
 * @return MyObject<glm::vec3> 
 */
MyObject<glm::vec3>* generateSphere (int id, glm::vec3 position, float radius, glm::vec3 col, bool normal_dir);


std::vector < Particle* > generateParticles (int nb_particles, glm::vec3 positionMin, glm::vec3 positionMax, float size, float life, glm::vec3 color);

bool check_collision_box(Particle *p, glm::vec3 box_min, glm::vec3 box_max);

bool check_collision(Particle* p1, Particle* p2);
bool check_collision(Particle *p, MyObject<glm::vec3> *obj);

void update_particles(std::vector< Particle *> particles, float dt, Scene<glm::vec3>* scene);