#pragma once

#include "_utils.hpp"

/**
 * @brief 
 * TODO
 * 
 * @param nb_cubes 
 * @param nb_lights 
 * @return Scene<glm::vec3>
 */
Scene<glm::vec3>* generateCubeScene (Camera* cam){
    // Maybe length = 20.0f to begin.
    float length = 50;
    float demi_length = length/2;

    Scene<glm::vec3>* myScene = new Scene<glm::vec3>(cam);
    Object<glm::vec3>* principalObj = generateCube (0, glm::vec3(-demi_length,demi_length,-demi_length), length, glm::vec3(0.2f,0.2f,0.2f), false);
    Object<glm::vec3>* floorCube = generateCube (1, glm::vec3(-demi_length, -demi_length/5, -demi_length), length, glm::vec3(0.8f,0.2f,0.2f), true);
    Object<glm::vec3>* leftCube = generateCube (2, glm::vec3(-length/4, demi_length/8, -demi_length), length/5, glm::vec3(0.8f,0.5f,0.1f), true);
    Object<glm::vec3>* rightCube = generateCube (3, glm::vec3(length/8, demi_length/8, -demi_length), length/8, glm::vec3(0.1f,0.6f,0.8f), true);

    Object<glm::vec3>* oneSphere = generateSphere (4, glm::vec3(0, demi_length/5.5, -demi_length/1.3f), 1.5, glm::vec3(0.7f, 0.3f, 0.05f));
    Object<glm::vec3>* twoSphere = generateSphere (5, glm::vec3(length/9, demi_length/9, -demi_length/1.3f), 2, glm::vec3(0.8f, 0.1f, 0.7f));
    Object<glm::vec3>* threeSphere = generateSphere (5, glm::vec3(0, demi_length/4.5, -demi_length/1.3f), 2, glm::vec3(0.9f, 0.1f, 0.1f));
    Object<glm::vec3>* foorSphere = generateSphere (5, glm::vec3(0, -demi_length/4, -demi_length/2), 5, glm::vec3(0.9f, 0.5f, 0.7f));

    myScene->addObject(principalObj);
    myScene->addObject(floorCube);
    myScene->addObject(leftCube);
    myScene->addObject(rightCube);
    myScene->addObject(oneSphere);
    myScene->addObject(twoSphere);
    myScene->addObject(threeSphere);
    myScene->addObject(foorSphere);
    

    myScene->addLight(new Light<glm::vec3> (0, glm::vec3(-length/4, length/8, -length/3), glm::vec3(0.1f, 0.1f, 0.7f)));
    myScene->addLight(new Light<glm::vec3> (1, glm::vec3(length/4, length/8, -length/3), glm::vec3(0.7f, 0.1f, 0.1f)));
    myScene->addLight(new Light<glm::vec3> (2, glm::vec3(0, length/8.5, -length/3), glm::vec3(0.1f, 0.7f, 0.1f)));
    // Back light, HIGH INTENSITY
    myScene->addLight(new Light<glm::vec3> (3, glm::vec3(0, length/8.5, +length/3), glm::vec3(200.0f, 100.0f, 20.0f)));

    ParticlesContainer *container = new ParticlesContainer(15, rightCube->getMinPosition(), rightCube->getMaxPosition());
    rightCube->setContainer(container);
    
    // TO SEE THE GRID OF PARTICLES
    // std::vector <Object<glm::vec3> *> grid = (create_grid_objects(rightCube, container->get_size()));
    // for (int i = 0; i < grid.size(); i++){
    //     myScene->addObject(grid[i]);
    // }

    // display in which grid the m_pos_min and m_pos_max are with the index of the grid
    glm::vec3 first_pos = glm::vec3(length/8, demi_length/8, -demi_length);
    glm::vec3 m_pos_min = rightCube->getMinPosition();
    glm::vec3 m_pos_max = rightCube->getMaxPosition();
    float spacing = container->get_size() * 2;
    int numx = (int) (m_pos_max.x - m_pos_min.x) / spacing;
    int numy = (int) (m_pos_max.y - m_pos_min.y) / spacing;
    int numz = (int) (m_pos_max.z - m_pos_min.z) / spacing;

    int i = ceil((m_pos_max.x - m_pos_min.x) / spacing);
    int j = ceil((m_pos_max.y - m_pos_min.y) / spacing);
    int k = ceil((m_pos_max.z - m_pos_min.z) / spacing);

    // std::cout << "Index min : " << i << " " << j << " " << k << std::endl;
    // std::cout << "Index real : " << i + j * numx + k * numx * numy << std::endl;

    // std::cout << "Id of this grid : " << grid[i + j * numx + k * numx * numy]->getId() << std::endl;

    return myScene;
}

/**
 * @brief 
 * 
 * @param id 
 * @param position Position of the top left back cube.
 * @param length Length of one edge  
 * @param colors Unique color for the entire cube.
 * @param normal_dir Direction of the normal (interior => false       exterior => true)
 * @return Object<glm::vec3> 
 */
Object<glm::vec3>* generateCube (int id, glm::vec3 position, float length, glm::vec3 col, bool normal_dir){

    std::vector<glm::vec3> vertices = generateCubeVertices(position, length, length);
    std::vector<glm::vec3> normal = generateCubeNormales(normal_dir);
    std::vector<unsigned int> indices = generateCubeIndices();
    Object<glm::vec3>* cube = new Object<glm::vec3>(id, vertices, normal, col, indices);
    cube->setType(0); // Cube
    cube->setMaxPosition(vertices[5]);
    cube->setMinPosition(vertices[3]);
    return cube;
}

std::vector < Object<glm::vec3> * > create_grid_objects (Object<glm::vec3>* m_object, float size){
    // m_grid_objects.clear();
    glm::vec3 m_pos_min = m_object->getMinPosition();
    glm::vec3 m_pos_max = m_object->getMaxPosition();

    float spacing = 2 * size;
    // int nb_voxel = std::pow(spacing,3);
    int nb_voxel_x = ceil (m_pos_max.x - m_pos_min.x) / spacing;
    int nb_voxel_y = ceil (m_pos_max.y - m_pos_min.y) / spacing;
    int nb_voxel_z = ceil (m_pos_max.z - m_pos_min.z) / spacing;
    std::vector < Object<glm::vec3> * > m_grid_objects(nb_voxel_x * nb_voxel_y * nb_voxel_z);
    glm::vec3 first_pos = m_object->getVertices()[0];

    for (int i = 0; i < nb_voxel_x; i++) {
        for (int j = 0; j < nb_voxel_y; j++) {
            for (int k = 0; k < nb_voxel_z; k++) {
                glm::vec3 pos = glm::vec3(first_pos.x + i * spacing ,first_pos.y + j * (-spacing),first_pos.z + k * spacing);
                Object<glm::vec3>* current_grid = generateCube (4, pos, spacing , glm::vec3(0.0f, 0.5f, 0.0f), true);
                current_grid->setContainer(new ParticlesContainer(0, current_grid->getMinPosition(), current_grid->getMaxPosition()));
                int idx = i + j * nb_voxel_x + k * nb_voxel_x * nb_voxel_y;
                m_grid_objects[idx] = current_grid;
                // std::cout << "Index : " << i << " " << j << " " << k << std::endl;
                // std::cout << "Index real: " << i + j * nb_voxel_x + k * nb_voxel_x * nb_voxel_y << std::endl;
            }
        }
    }
    // std::cout << "Taille de la grille ? " << m_grid_objects.size() << std::endl;
    // std::cout << "Taille de la grille ? " << nb_voxel_x * nb_voxel_y * nb_voxel_z << std::endl;

    return m_grid_objects;
}


Object<glm::vec3>* generateSphere (int id, glm::vec3 center, float radius, glm::vec3 col){
    int stack = 100;
    int slice = 100;
    glm::vec3 color = col;
    std::vector <glm::vec3> vertices = generateSphereVertices(center, radius, stack, slice);
    std::vector <unsigned int> indices = generateSphereIndices(stack, slice);
    std::vector <glm::vec3> normales = generateSphereNormales(center, vertices);

    Object<glm::vec3>* sphere = new Object<glm::vec3>(id, vertices, normales, color, indices);
    sphere->setType(1); // Sphere
    sphere->setMaxPosition(center);
    sphere->setMinPosition(center);
    return sphere;
}
