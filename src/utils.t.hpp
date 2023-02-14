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
Scene<glm::vec3>* generateCubeScene (Camera* cam, glm::vec3 position, float length, int nb_cubes, int nb_lights){
    // Maybe length = 20.0f to begin.
    Scene<glm::vec3>* myScene = new Scene<glm::vec3>(cam);
    MyObject<glm::vec3>* principalObj = generateCube (0, glm::vec3(-length/2,length/2,-length/2), length, glm::vec3(0.2f,0.2f,0.2f), false);

    myScene->addObject(principalObj);

    float min_pos = -length/2;
    float max_pos = length/2;

    for (int i = 1; i <= nb_cubes; i++){
        float cubeLength = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(length/2)));
        float x_pos = (min_pos) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((max_pos-cubeLength)-min_pos)));
        float y_pos = min_pos + cubeLength + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((max_pos-cubeLength)-min_pos)));
        float z_pos = min_pos + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((max_pos-cubeLength)-min_pos)));
        
        float random_col_1 = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX));
        float random_col_2 = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX));
        float random_col_3 = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX));
        glm::vec3 random_col = glm::vec3 (random_col_1, random_col_2, random_col_3);

        MyObject<glm::vec3>* randCube = generateCube (i, glm::vec3(x_pos, y_pos, z_pos), cubeLength, random_col, true);
        myScene->addObject(randCube);
    }
    
    for (int i = 0; i < nb_lights; i++){
        float random_col_1 = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX));
        float random_col_2 = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX));
        float random_col_3 = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX));
        glm::vec3 random_col = glm::vec3 (random_col_1, random_col_2, random_col_3);

        float x_pos = min_pos + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max_pos-min_pos)));
        float y_pos = min_pos + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max_pos-min_pos)));
        float z_pos = min_pos + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max_pos-min_pos)));
        glm::vec3 random_pos = glm::vec3 (x_pos, y_pos, z_pos);

        myScene->addLight(new Light<glm::vec3> (i, random_pos, random_col));
    }

    return myScene;
}


/**
 * @brief 
 * TODO
 * 
 * @param nb_sphere 
 * @param nb_lights 
 * @return MyObject<glm::vec3> 
 */
Scene<glm::vec3>* generateSphereScene (glm::vec3 position_min, glm::vec3 position_max, int nb_sphere, int nb_lights){
    return nullptr;
}




/**
 * @brief Generates a cube (or a rectangular shape).
 * 
 * @param position of the top left back vertex
 * @param length1 
 * @param length2 
 * @return std::vector<glm::vec3> 
 */
std::vector<glm::vec3> generateCubeVertices(glm::vec3 position, float length1, float length2){

    std::vector<glm::vec3> vertices;

    // if the origin and positions are like that : 
    //
    //     |
    //     |
    //    O ----->
    //      \
    //       \
    ////////////////////////////////////////////////
    vertices.push_back(position);
    vertices.push_back(glm::vec3(position[0], position[1], position[2]+length1)); // top left front
    vertices.push_back(glm::vec3(position[0], position[1]-length1, position[2]+length1)); // bottom left front
    vertices.push_back(glm::vec3(position[0], position[1]-length1, position[2])); // bottom left back

    vertices.push_back(glm::vec3(position[0]+length2, position[1], position[2]));
    vertices.push_back(glm::vec3(position[0]+length2, position[1], position[2]+length1));
    vertices.push_back(glm::vec3(position[0]+length2, position[1]-length1, position[2]+length1));
    vertices.push_back(glm::vec3(position[0]+length2, position[1]-length1, position[2]));

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

    indices.push_back(0); 
    indices.push_back(1); 
    indices.push_back(2);
    
    indices.push_back(0);
    indices.push_back(3);
    indices.push_back(2);
    
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(5);
    
    indices.push_back(0);
    indices.push_back(4);
    indices.push_back(5);
    
    indices.push_back(0);
    indices.push_back(4);
    indices.push_back(7);

    indices.push_back(0);
    indices.push_back(3);
    indices.push_back(7);

    indices.push_back(6);
    indices.push_back(7);
    indices.push_back(3);

    indices.push_back(6);
    indices.push_back(2);
    indices.push_back(3);

    indices.push_back(6);
    indices.push_back(5);
    indices.push_back(4);

    indices.push_back(6);
    indices.push_back(7);
    indices.push_back(4);

    indices.push_back(6);
    indices.push_back(2);
    indices.push_back(1);

    indices.push_back(6);
    indices.push_back(5);
    indices.push_back(1);

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
    glm::vec3 mid = glm::vec3 ((vertices[0][0] + vertices[6][0])/2, (vertices[0][1] + vertices[6][1])/2, (vertices[0][2] + vertices[6][2])/2 );

    for (int i = 0; i < vertices.size(); i++){
        glm::vec3 norm = glm::normalize(glm::vec3 (vertices[i][0] - mid[0], vertices[i][1] - mid[1], vertices[i][2] - mid[2]));
        if (! normal_dir)
            norm *= (-1);
        normales.push_back(norm);
    }
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
 * @return MyObject<glm::vec3> 
 */
MyObject<glm::vec3>* generateCube (int id, glm::vec3 position, float length, glm::vec3 col, bool normal_dir){

    std::vector<glm::vec3> vertices = generateCubeVertices(position, length, length);
    std::vector<glm::vec3> normal = generateCubeNormales(vertices, normal_dir);
    std::vector<unsigned int> indices = generateCubeIndices();
    
    return new MyObject<glm::vec3>(id, vertices, normal, col, indices);
}

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
MyObject<glm::vec3>* generateSphere (int id, glm::vec3 position, float radius, glm::vec4 col, bool normal_dir){
    return nullptr;
}