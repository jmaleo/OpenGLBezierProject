#pragma once

#include "_utils.hpp"

/**
 * @brief 
 * TODO
 * 
 * @param nb_cubes 
 * @param nb_lights 
 * @return MyObject<glm::vec3> 
 */
Scene<glm::vec3> generateCubeScene (glm::vec3 position_min, glm::vec3 position_max, int nb_cubes, int nb_lights){
    return Scene<glm::vec3>();
}


/**
 * @brief 
 * TODO
 * 
 * @param nb_sphere 
 * @param nb_lights 
 * @return MyObject<glm::vec3> 
 */
Scene<glm::vec3> generateSphereScene (glm::vec3 position_min, glm::vec3 position_max, int nb_sphere, int nb_lights){
    return Scene<glm::vec3>();
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
    //     | /
    //     |/
    //    O ----->
    //
    ////////////////////////////////////////////////
    vertices.push_back(position);
    vertices.push_back(glm::vec3(position[0], position[1], position[2]-length1)); // top left front
    vertices.push_back(glm::vec3(position[0], position[1]-length1, position[2]-length1)); // bottom left front
    vertices.push_back(glm::vec3(position[0], position[1]-length1, position[2])); // bottom left back

    vertices.push_back(glm::vec3(position[0]+length2, position[1], position[2]));
    vertices.push_back(glm::vec3(position[0]+length2, position[1], position[2]-length1));
    vertices.push_back(glm::vec3(position[0]+length2, position[1]-length1, position[2]-length1));
    vertices.push_back(glm::vec3(position[0]+length2, position[1]-length1, position[2]));

    return vertices;
}

/**
 * @brief Generates Indices of the prism or cube.
 * 
 * @param vertices 
 * @return std::vector<int> 
 */
std::vector<int> generateCubeIndices (){
    std::vector<int> indices;

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
 * @param position Position of the top left back cube.
 * @param length Length of one edge  
 * @param colors Unique color for the entire cube.
 * @param normal_dir Direction of the normal (interior => false       exterior => true)
 * @return MyObject<glm::vec3> 
 */
MyObject<glm::vec3> generateCube (glm::vec3 position, float length, glm::vec4 col, bool normal_dir){

    std::vector<glm::vec3> vertices = generateCubeVertices(position, length, length);
    std::vector<glm::vec3> normal = generateCubeNormales(vertices, normal_dir);
    std::vector<int> indices = generateCubeIndices();
    std::vector<glm::vec4> colors = generateColors(col, vertices.size());
    
    return MyObject<glm::vec3>();
}

/**
 * @brief 
 * 
 * @param position Position of the sphere.
 * @param radius Radius of the Sphere
 * @param colors Unique color for the entire sphere
 * @param normal_dir Direction of the normal (interior => false       exterior => true)
 * @return MyObject<glm::vec3> 
 */
MyObject<glm::vec3> generateSphere (glm::vec3 position, float radius, glm::vec4 col, bool normal_dir){
    return MyObject<glm::vec3>();
}

/**
 * @brief Generates a vector containing nb_elem of the same value (color).
 * 
 * @param col 
 * @param nb_elem 
 * @return std::vector<glm::vec4> 
 */
std::vector<glm::vec4> generateColors (glm::vec4 col, int nb_elem){
    std::vector<glm::vec4> colors; 
    for (int i = 0; i < nb_elem; i++){
        colors.push_back (col);
    } 
    return colors;
}