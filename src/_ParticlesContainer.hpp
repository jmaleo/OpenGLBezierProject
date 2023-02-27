#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <math.h>

#include "Particle.t.hpp"
// #include "Object.t.hpp"


class ParticlesContainer {

    public : 

        ParticlesContainer(int nb_particles_per_side, glm::vec3 pos_min, glm::vec3 pos_max);

        void update (float dt);

        std::vector < glm::vec3 > get_positions();

        glm::vec3 get_color() { return m_particles[0].get_material()->color; }
        float get_size() { return m_particles[0].get_carac()->size; }

        unsigned int* get_particleVAO() { return &particleVAO; }

        unsigned int* get_particleVBO() { return &particleVBO; }

        bool is_setUp() { return m_setUp; }
        void set_setUp(bool setUp) { m_setUp = setUp; }

        int get_number_particles () { return m_particles.size(); }

    private : 

        unsigned int particleVAO;
        unsigned int particleVBO;

        bool m_setUp = false;

        std::vector < glm::vec3 > edges;
        std::vector < int > lines;

        std::vector < Particle > m_particles;

        std::vector < std::vector <int> > m_voxelGrid;

        glm::vec3 m_pos_min;
        glm::vec3 m_pos_max;
        CaracParticle m_carac;
        Material m_mat;

        bool m_once_update = false;


        void m_create_particles (int nb_particles_per_side);
        void m_create_voxelGrid ();

        // void m_particles_collisions ();
        // void resolve_collision (Particle* p1, Particle* p2);
        bool is_in_collision (Particle p1, Particle p2);

};