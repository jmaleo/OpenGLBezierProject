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

    myScene->addObject(principalObj);
    myScene->addObject(floorCube);
    myScene->addObject(leftCube);
    myScene->addObject(rightCube);

    myScene->addLight(new Light<glm::vec3> (0, glm::vec3(-length/4, length/8, -length/3), glm::vec3(0.1f, 0.1f, 0.7f)));
    myScene->addLight(new Light<glm::vec3> (1, glm::vec3(length/4, length/8, -length/3), glm::vec3(0.7f, 0.1f, 0.1f)));
    myScene->addLight(new Light<glm::vec3> (2, glm::vec3(0, length/8.5, -length/3), glm::vec3(0.1f, 0.7f, 0.1f)));
    // Back light, HIGH INTENSITY
    myScene->addLight(new Light<glm::vec3> (3, glm::vec3(0, length/8.5, +length/3), glm::vec3(200.0f, 100.0f, 20.0f)));

    ParticlesContainer *container = new ParticlesContainer(5, rightCube->getMinPosition(), rightCube->getMaxPosition());
    rightCube->setContainer(container);
    
    
    std::vector <Object<glm::vec3> *> grid = (create_grid_objects(rightCube, container->get_size()));
    for (int i = 0; i < grid.size(); i++){
        myScene->addObject(grid[i]);
    }

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


/**
 * @brief Generates normales of given vertices, for a cube of prism.
 * 
 * @param vertices 
 * @return std::vector <glm::vec3> 
 */
std::vector <glm::vec3> generateCubeNormales (std::vector <glm::vec3> vertices, bool normal_dir){
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
    // std::cout << "Il y a " << vertices.size() << " vertices et " << normales.size() << " normales" << std::endl;
    return normales;
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
    std::vector<glm::vec3> normal = generateCubeNormales(vertices, normal_dir);
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