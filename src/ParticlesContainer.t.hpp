#pragma once

#include "_ParticlesContainer.hpp"

ParticlesContainer::ParticlesContainer(int nb_particles_per_side, glm::vec3 pos_min, glm::vec3 pos_max){

    m_carac = initialiseCaracParticle();
    m_mat = initialiseMaterial();

    // m_carac.velocity = glm::vec3(0.0f, -0.1f, 0.05f);
    m_carac.acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

    m_pos_max = pos_max;
    m_pos_min = pos_min;
    m_mat.color = glm::vec3 (1.0f, 0.0f, 0.0f);
    m_carac.size = 0.5f;

    m_create_particles (nb_particles_per_side);
    m_create_voxelGrid ();
}


std::vector < glm::vec3 > ParticlesContainer::get_positions(){
    std::vector < glm::vec3 > positions;
    for (int i = 0; i < m_particles.size(); i++) {
        positions.push_back(m_particles[i].get_carac()->position);
    }
    return positions;
}

void ParticlesContainer::update (float dt){
    CaracParticle* current_carac;
    m_particles_collisions ();

    m_create_voxelGrid ();

    // for (int i = 0; i < m_particles.size(); i++) {
    //     m_particles[i].update();
    // }

    for (int i = 0; i < m_particles.size(); i++) {
        // update the particles 
        current_carac = m_particles[i].get_carac();

        current_carac->position += current_carac->velocity * dt;
        // current_carac->velocity += current_carac->acceleration * dt;
        // current_carac->acceleration *= 0.9f;
        // Update the acceleration, velocity and position like a fluid
        // current_carac->acceleration = glm::vec3(0.0f, 0.0f , 0.0f);
        // check if the particles are out of the box
        if (current_carac->position.x > m_pos_max.x) {
            current_carac->position.x = m_pos_max.x;
            current_carac->velocity.x *= -1;
        }
        if (current_carac->position.x < m_pos_min.x) {
            current_carac->position.x = m_pos_min.x;
            current_carac->velocity.x *= -1;
        }
        if (current_carac->position.y > m_pos_max.y) {
            current_carac->position.y = m_pos_max.y;
            current_carac->velocity.y *= -1;
        }
        if (current_carac->position.y < m_pos_min.y) {
            current_carac->position.y = m_pos_min.y;
            current_carac->velocity.y *= -1;
        }
        if (current_carac->position.z > m_pos_max.z) {
            current_carac->position.z = m_pos_max.z;
            current_carac->velocity.z *= -1;
        }
        if (current_carac->position.z < m_pos_min.z) {
            current_carac->position.z = m_pos_min.z;
            current_carac->velocity.z *= -1;
        }

        current_carac->life -= dt;

        if (current_carac->life < 0.0f){
            current_carac->life = 0.0f;
            m_particles.erase(m_particles.begin() + i);
        }
    }
    // return;
}

void ParticlesContainer::m_create_particles (int nb_particles_per_side){
    // generate a uniforme distribution of particles
    m_particles.clear();
    float x_offset = (m_pos_max.x - m_pos_min.x) / nb_particles_per_side;
    float y_offset = (m_pos_max.y - m_pos_min.y) / nb_particles_per_side;
    float z_offset = (m_pos_max.z - m_pos_min.z) / nb_particles_per_side;

    float begin_x = m_pos_min.x + x_offset/2;
    float begin_y = m_pos_min.y + y_offset/2;
    float begin_z = m_pos_min.z + z_offset/2;


    for (int i = 0; i < nb_particles_per_side; i++) {
        for (int j = 0; j < nb_particles_per_side; j++) {
            for (int k = 0; k < nb_particles_per_side; k++) {
                glm::vec3 pos = glm::vec3(
                    begin_x + i * x_offset, 
                    begin_y + j * y_offset, 
                    begin_z + k * z_offset);
                // create a velocity like little gravity
                m_carac.velocity = glm::vec3(0.0f, -0.1f, 0.1f);
                // m_carac.acceleration = glm::vec3(0.0f, -0.3f, 0.0f);
                m_carac.position = pos;
                m_carac.life = 500 + rand () % 2000;
                m_particles.push_back(Particle(m_carac, m_mat));
            }
        }
    }
    createColor(true);
}

void ParticlesContainer::m_create_voxelGrid (){
    float spacing = 2 * m_carac.size;
    int numx = ceil (m_pos_max.x - m_pos_min.x) / spacing;
    int numy = ceil (m_pos_max.y - m_pos_min.y) / spacing;
    int numz = ceil (m_pos_max.z - m_pos_min.z) / spacing;
    
    if (m_voxelGrid.size() != (numx) * (numy) * (numz))
        m_voxelGrid.resize((numx) * (numy) * (numz));

    for (int i = 0; i < m_voxelGrid.size(); i++) {
        m_voxelGrid[i].clear();
    }

    for (int i = 0; i < m_particles.size(); i++) {
        glm::vec3 pos = m_particles[i].get_carac()->position;

        int x = floor (pos.x - m_pos_min.x) / spacing;
        int y = floor (pos.y - m_pos_min.y) / spacing;
        int z = floor (pos.z - m_pos_min.z) / spacing;
        int index = x + y * numx + z * numx * numy;

        if (index >= m_voxelGrid.size()) {
            index = m_voxelGrid.size() - 1;
        }
        m_voxelGrid[index].push_back(i);
    }

}

bool ParticlesContainer::is_in_collision (Particle p1, Particle p2){
    glm::vec3 pos1 = p1.get_carac()->position;
    glm::vec3 pos2 = p2.get_carac()->position;
    float dist = glm::distance(pos1, pos2);
    if (dist <= 2 * m_carac.size) {
        return true;
    }
    return false;

}

// this function check the collision between particles
void ParticlesContainer::m_particles_collisions(){
    
    float spacing = 2 * m_carac.size;
    int numx = ceil (m_pos_max.x - m_pos_min.x) / spacing;
    int numy = ceil (m_pos_max.y - m_pos_min.y) / spacing;
    int numz = ceil (m_pos_max.z - m_pos_min.z) / spacing;

    
    for (int i = 0; i < m_particles.size(); i++) {
        
        glm::vec3 pos = m_particles[i].get_carac()->position;

        int x = floor (pos.x - m_pos_min.x) / spacing;
        int y = floor (pos.y - m_pos_min.y) / spacing;
        int z = floor (pos.z - m_pos_min.z) / spacing;
        
        int index = x + y * numx + z * numx * numy;
        if (index >= m_voxelGrid.size()) {
            index = m_voxelGrid.size() - 1;
        }
        
        for (int j = 0; j < m_voxelGrid[index].size(); j++) {
            
            int index2 = m_voxelGrid[index][j];
            if (index2 != i) {
                if (is_in_collision(m_particles[i], m_particles[index2])) {
                    // check the distance between the two particles
                    float dist = glm::distance(m_particles[i].get_carac()->position, m_particles[index2].get_carac()->position);
                    // If the distance is extremely small, we continue, to avoid division by 0
                    if (dist < 0.001 && dist > -0.001) {
                        continue;
                    }
                    glm::vec3 v1 = m_particles[i].get_carac()->velocity;
                    glm::vec3 v2 = m_particles[index2].get_carac()->velocity;

                    glm::vec3 p1 = m_particles[i].get_carac()->position;
                    glm::vec3 p2 = m_particles[index2].get_carac()->position;

                    glm::vec3 n = glm::normalize(p2 - p1);
                    
                    glm::vec3 v1n = glm::dot(v1, n) * n;
                    glm::vec3 v1t = v1 - v1n;
                    
                    glm::vec3 v2n = glm::dot(v2, n) * n;
                    glm::vec3 v2t = v2 - v2n;

                    glm::vec3 v1t2n = v1t + v2n;
                    glm::vec3 v2t2n = v2t + v1n;
                    
                    m_particles[i].get_carac()->velocity = v1t2n;
                    m_particles[index2].get_carac()->velocity = v2t2n;
                }
            }
        }   
    }
    
    
}

void ParticlesContainer::m_create_particles_center(int nb_particles){
    glm::vec3 cube_center = (m_pos_max + m_pos_min) / 2.0f;
    // Create the particles in the center of the cube, following a little bit the cube shape.
    float distance_to_center = glm::distance(m_pos_max, m_pos_min) / 2.0f;
    
    // Creation of two cube of particles, in the middle of the cube.
    // for (int i = 0; i < nb_particles; i++) {
    //     //generates a position in the center, with a random distance to the center.
    //     float dir = (rand() % 2 == 0) ? -1 : 1;
    //     float x = cube_center.x + dir * (rand() % 10) / 10.0f * distance_to_center/5;
    //     float y = cube_center.y + dir * (rand() % 10) / 10.0f * distance_to_center/5;
    //     float z = cube_center.z + dir * (rand() % 10) / 10.0f * distance_to_center/5;
    //     glm::vec3 pos = glm::vec3(x, y, z);
    //     // put the direction of the velocity in the inverse direction of the center of the cube.
    //     glm::vec3 vel = glm::normalize(pos - cube_center) * 0.5f;
    //     m_carac.position = pos;
    //     m_carac.velocity = vel;
    //     m_carac.life = 50 + rand () % 100;
    //     m_particles.push_back(Particle(m_carac, m_mat));
    // }

    // Creation of a cube of particles, in the middle of the cube.
    for (int i = 0; i < nb_particles; i++) {
        // random creation of a position INTO the cube given by its new_min_pos and new_max_pos.
        // Around the center of the cube.
        float random_dir_x = (rand() % 2 == 0) ? -1 : 1;
        float random_dir_y = (rand() % 2 == 0) ? -1 : 1;
        float random_dir_z = (rand() % 2 == 0) ? -1 : 1;
        float x = cube_center.x + random_dir_x * (rand() % 10) / 10.0f * distance_to_center/5.0f;
        float y = cube_center.y + random_dir_y * (rand() % 10) / 10.0f * distance_to_center/5.0f;
        float z = cube_center.z + random_dir_z * (rand() % 10) / 10.0f * distance_to_center/5.0f;

        glm::vec3 pos = glm::vec3(x, y, z);

        
        // put the direction of the velocity in the inverse direction of the center of the cube.
        glm::vec3 vel = glm::normalize(cube_center - pos) * 0.5f;
        m_carac.position = pos;
        m_carac.velocity = vel;
        m_carac.life = 50 + rand () % 100;
        m_particles.push_back(Particle(m_carac, m_mat));
    }

    createColor(false);
    // float max_dist_to_center = distance_to_center + ;
}

// Position : 1 for uniform disposition and 0 for the center.
void ParticlesContainer::resetParticles(int nb_particles_per_side, int position){
    m_particles.clear();
    if (position == 1){
        m_create_particles(nb_particles_per_side);
    }
    if (position == 0){
        m_create_particles_center(pow(nb_particles_per_side, 3.0f));
    }
    m_create_voxelGrid();
}

/**
 * @brief Create the particles' color in the cube.
 * if random is true, the color is random, near a red color, 
 * else (so if the particles is near the center) the color is a fade from yellow (center) to red to dark (far).
 */
void ParticlesContainer::createColor (bool random){
    m_colors.clear();
    for (auto particle : m_particles){
        if (random){
            float glow = 3.f;
            // Create a shiny color near the red color
            glm::vec3 rand_color = glm::vec3(0.8f, 0.0f, 0.0f) + glm::vec3(glow, glow, glow);
            m_colors.push_back(rand_color);
            particle.get_material()->color = rand_color;
        }
        else{
            glm::vec3 pos = particle.get_carac()->position;
            float dist = glm::distance(pos, (m_pos_max + m_pos_min) / 2.0f);
            float max_dist = glm::distance(m_pos_max, m_pos_min) / 2.0f;
            float ratio = dist / max_dist;

            // Create a color from yellow to red to dark with little glowy effect
            glm::vec3 glow = glm::vec3(1.1f, 1.0f, 0.5f) * glm::vec3(0.5f + 0.5f * cos(ratio * 10.0f));
            glm::vec3 color = glm::vec3(0.8f - ratio, ratio, 0.0f) + glow;
            m_colors.push_back(color);
            particle.get_material()->color = color;
        }
    }
}