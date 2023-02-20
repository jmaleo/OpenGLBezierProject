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
    MyObject<glm::vec3>* principalObj = generateCube (0, glm::vec3(-demi_length,demi_length,-demi_length), length, glm::vec3(0.2f,0.2f,0.2f), false);
    MyObject<glm::vec3>* floor = generateCube (1, glm::vec3(-demi_length, -demi_length/5, -demi_length), length, glm::vec3(0.8f,0.2f,0.2f), true);
    MyObject<glm::vec3>* leftCube = generateCube (2, glm::vec3(-length/4, demi_length/8, -demi_length), length/5, glm::vec3(0.8f,0.5f,0.1f), true);
    MyObject<glm::vec3>* rightCube = generateCube (3, glm::vec3(length/8, demi_length/8, -demi_length), length/8, glm::vec3(0.1f,0.6f,0.8f), true);

    myScene->addObject(principalObj);
    myScene->addObject(floor);
    myScene->addObject(leftCube);
    myScene->addObject(rightCube);

    myScene->addLight(new Light<glm::vec3> (0, glm::vec3(-length/4, length/8, -length/3), glm::vec3(0.1f, 0.1f, 0.7f)));
    myScene->addLight(new Light<glm::vec3> (1, glm::vec3(length/4, length/8, -length/3), glm::vec3(0.7f, 0.1f, 0.1f)));
    myScene->addLight(new Light<glm::vec3> (2, glm::vec3(0, length/8.5, -length/3), glm::vec3(0.1f, 0.7f, 0.1f)));
    // Back light, HIGH INTENSITY
    myScene->addLight(new Light<glm::vec3> (3, glm::vec3(0, length/8.5, +length/3), glm::vec3(200.0f, 100.0f, 20.0f)));

    // generate pos min and max for a little box of 5 by 5 by 5 in front of the camera (in the middle of the scene)
    glm::vec3 positionMin = rightCube->getMinPosition();
    glm::vec3 positionMax = rightCube->getMaxPosition();

    std::vector < Particle * > particules = generateParticles (10, positionMin, positionMax, 1, 100, glm::vec3(1.8f, 0.1f, 0.1f));
    myScene->addParticles(particules);

    return myScene;
}

/**
 * @brief 
 * TODO
 * 
 * @param nb_cubes 
 * @param nb_lights 
 * @return Scene<glm::vec3>
 */
Scene<glm::vec3>* generateRandomCubeScene (Camera* cam, glm::vec3 position, float length, int nb_cubes, int nb_lights){
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
    std::cout << "Il y a " << vertices.size() << " vertices et " << normales.size() << " normales" << std::endl;
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
    MyObject<glm::vec3>* cube = new MyObject<glm::vec3>(id, vertices, normal, col, indices);
    cube->setType(0); // Cube
    cube->setMaxPosition(vertices[0]);
    cube->setMinPosition(vertices[6]);
    return cube;
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



// function that check the collision between a particle and a box and make the difference if the particle is inside or outside the box
bool check_collision_box(Particle *p, glm::vec3 box_min, glm::vec3 box_max) {
    glm::vec3 particle_pos = p->get_position();
    float particle_radius = p->get_size();
    
    // Test if the particle is outside the box
    bool outside = false;
    for (int i = 0; i < 3; i++) {
        if (particle_pos[i] - particle_radius > box_max[i] || particle_pos[i] + particle_radius < box_min[i]) {
            outside = true;
            break;
        }
    }
    // if (!outside) {
    //     return false; // Particle is entirely inside the box
    // }
    
    // Test if the particle intersects the box
    float distance = 0.0f;
    for (int i = 0; i < 3; i++) {
        if (particle_pos[i] < box_min[i]) {
            distance += pow(particle_pos[i] - box_min[i], 2);
        } else if (particle_pos[i] > box_max[i]) {
            distance += pow(particle_pos[i] - box_max[i], 2);
        }
    }
    return distance < pow(particle_radius, 2);
}

// Check the collision between a particle and the bounding box of a cube (MyObject) and make a difference if the object is a cube or a sphere
bool check_collision(Particle *p, MyObject<glm::vec3> *obj) {
    if (obj->getType() == 0) { // Cube
        glm::vec3 min = obj->getMinPosition();
        glm::vec3 max = obj->getMaxPosition();
        check_collision_box(p, min, max);
    } else { // Sphere
        glm::vec3 center = obj->getCenterPosition();
        glm::vec3 pos = p->get_position();
        float size = p->get_size();
        float radius = obj->getRadius();
        return glm::distance(pos, center) < size + radius;
    }
}

bool check_collision(Particle* p1, Particle* p2){
    glm::vec3 pos1 = p1->get_position();
    glm::vec3 pos2 = p2->get_position();
    float size1 = p1->get_size();
    float size2 = p2->get_size();
    return glm::distance(pos1, pos2) < size1 + size2;
}

std::vector <Particle *> generateParticles (int nb_particles, glm::vec3 positionMin, glm::vec3 positionMax, float size, float life, glm::vec3 color){
    std::vector < Particle* > particles;
    glm::vec3 velocity = glm::vec3(0.0f, -0.01f, 0.0f);
    glm::vec3 acceleration = glm::vec3 (0.0f);
    // width 
    float width = positionMax.x - positionMin.x;
    // height
    float height = positionMax.y - positionMin.y;
    // depth
    float depth = positionMax.z - positionMin.z;
    // x step
    float x_step = width / nb_particles;
    // y step
    float y_step = height / nb_particles;

    for (int i = 0; i < nb_particles; i++){
        for (int j = 0; j < nb_particles; j++){
            for (int k = 0; k < nb_particles; k++){
                glm::vec3 position = glm::vec3(
                    positionMin.x + x_step * i,
                    positionMin.y + y_step * j,
                    positionMin.z + x_step * k
                );
                Particle * part = new  Particle( position, color,  velocity,  acceleration, life, size);
                particles.push_back(part);
            }
        }
    }
    std::cout << " particles size : " << particles.size() << std::endl;
    return particles;
}


void update_particles (std::vector <Particle *> particles, float dt){
    const float gravity = 9.8f;
    const float viscosity = 0.1f;

    for (int i = 0; i < particles.size(); i++) {
        Particle* p1 = particles[i];
        // Mise à jour de la position et de la vitesse
        p1->set_position(p1->get_position() + p1->get_velocity() * dt);
        p1->set_velocity(p1->get_velocity() + p1->get_acceleration() * dt);

        for (int j = i + 1; j < particles.size(); j++) {
            Particle* p2 = particles[j];
            if (check_collision(p1, p2)) {
                std::cout << "collision" << std::endl;
                glm::vec3 dir = glm::normalize(p2->get_position() - p1->get_position());
                float distance = glm::length(p2->get_position() - p1->get_position());
                glm::vec3 v1 = glm::dot(p1->get_velocity(), dir) * dir;
                glm::vec3 v2 = glm::dot(p2->get_velocity(), dir) * dir;
                glm::vec3 new_v1 = (p1->get_mass() - p2->get_mass()) / (p1->get_mass() + p2->get_mass()) * v1 + 2.0f * p2->get_mass() / (p1->get_mass() + p2->get_mass()) * v2;
                glm::vec3 new_v2 = (p2->get_mass() - p1->get_mass()) / (p1->get_mass() + p2->get_mass()) * v2 + 2.0f * p1->get_mass() / (p1->get_mass() + p2->get_mass()) * v1;
                p1->set_velocity(p1->get_velocity() + viscosity * (new_v1 - v1));
                p2->set_velocity(p2->get_velocity() + viscosity * (new_v2 - v2));
                p1->set_position(p1->get_position() + (distance - (p1->get_size() + p2->get_size())) * dir * 0.5f);
                p2->set_position(p2->get_position() - (distance - (p1->get_size() + p2->get_size())) * dir * 0.5f);
            }
        }
    }
}


void update_particles(std::vector< Particle *> particles, float dt, Scene<glm::vec3>* scene) {
    for (auto p : particles) {
    //     if (p->is_alive()) {
    //         // Compute resulting acceleration
            

    //         bool collision = false;
    //         // Check for collisions with objects in the scene
    //         for (auto obj : scene->getListObjects()) {
    //             if (check_collision(p, obj)) {
    //                 collision = true;
    //               // std::cout << "Collision" << std::endl;
    //               // Implementation of the update when there is a collision
    //             //   std::vector <glm::vec3> normals = obj->getNormales();
    //             }
    //         }
    //         if (collision) {
    //             std::cout << "Collision" << std::endl;  
    //         }
    //         else{
    //             glm::vec3 acceleration = glm::vec3(0.0f, -9.81f, 0.0f); // Gravity
    //             acceleration -= p->get_velocity() * 0.1f; // Viscosity
    //             // TODO: add other forces as needed
                
    //             // Update velocity and position using numerical integration
    //             glm::vec3 velocity = p->get_velocity() + acceleration * dt;
    //             glm::vec3 position = p->get_position() + velocity * dt;
    //             p->set_velocity(velocity);
    //             p->set_position(position);
    //             p->set_life(p->get_life() - dt);
    //         }
    //         // Update particle properties
    //     }
        bool collision = false;
        for (auto obj : scene->getListObjects()) {
            if (check_collision(p, obj)) {
                collision = true;
                // std::cout << "Collision" << std::endl;
                // Implementation of the update when there is a collision
            //   std::vector <glm::vec3> normals = obj->getNormales();
            }
        }
        if (!collision)
            p->set_position(p->get_position() + p->get_velocity() * dt);
    }
}