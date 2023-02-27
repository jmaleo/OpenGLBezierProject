#pragma once

#include "_ParticlesContainer.hpp"

ParticlesContainer::ParticlesContainer(int nb_particles_per_side, glm::vec3 pos_min, glm::vec3 pos_max){

    m_carac = initialiseCaracParticle();
    m_mat = initialiseMaterial();

    m_carac.velocity = glm::vec3(0.0f, -0.1f, 0.0f);
    m_carac.acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

    m_pos_max = pos_max;
    m_pos_min = pos_min;
    m_mat.color = glm::vec3 (1.0f, 0.0f, 0.0f);
    m_carac.size = 0.5f;

    m_create_particles (nb_particles_per_side);
    m_create_voxelGrid ();

    // std::cout << "ParticlesContainer created" << std::endl;
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

    // m_particles_collisions ();
    m_create_voxelGrid ();

    for (int i = 0; i < m_particles.size(); i++) {
        m_particles[i].update();
    }

    for (int i = 0; i < m_particles.size(); i++) {
        // update the particles 
        current_carac = m_particles[i].get_carac();
        // current_carac->position += current_carac->velocity * dt;
        // current_carac->velocity += current_carac->acceleration * dt;
        // current_carac->acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
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
    }


    return;
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
                m_carac.position = pos;
                m_particles.push_back(Particle(m_carac, m_mat));
            }
        }
    }
}
void ParticlesContainer::m_create_voxelGrid (){
    float spacing = 2 * m_carac.size;
    int numx = ceil (m_pos_max.x - m_pos_min.x) / spacing;
    int numy = ceil (m_pos_max.y - m_pos_min.y) / spacing;
    int numz = ceil (m_pos_max.z - m_pos_min.z) / spacing;
    m_voxelGrid.clear();
    m_voxelGrid.resize((numx) * (numy) * (numz));

    for (int i = 0; i < m_particles.size(); i++) {
        glm::vec3 pos = m_particles[i].get_carac()->position;

        int x = floor (pos.x - m_pos_min.x) / spacing;
        int y = floor (pos.y - m_pos_min.y) / spacing;
        int z = floor (pos.z - m_pos_min.z) / spacing;
        int index = x + y * numx + z * numx * numy;
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