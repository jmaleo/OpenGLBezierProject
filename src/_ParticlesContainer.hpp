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
        std::vector < glm::vec3 > get_colors() { return m_colors; }

        glm::vec3 get_color() { return m_mat.color; }
        float get_size() { return m_carac.size; }

        unsigned int* get_particleVAO() { return &particleVAO; }

        unsigned int* get_particleVBO() { return &particleVBO; }

        unsigned int* get_particleVBO_color() { return &particleVBO_color; }

        bool is_setUp() { return m_setUp; }
        void set_setUp(bool setUp) { m_setUp = setUp; }

        int get_number_particles () { return m_particles.size(); }

        // Position : 1 for uniform disposition and 0 for the center.
        void resetParticles(int nb_particles_per_side, int position);


        /**
         * @brief Create the particles' color in the cube.
         * if random is true, the color is random, near a red color, 
         * else (so if the particles is near the center) the color is a fade from yellow (center) to red to dark (far).
         */
        void createColor (bool random);

    private : 

        unsigned int particleVAO;
        unsigned int particleVBO;
        unsigned int particleVBO_color;

        bool m_setUp = false;

        std::vector < glm::vec3 > edges;
        std::vector < int > lines;

        std::vector < Particle > m_particles;
        std::vector < glm::vec3 > m_colors;

        std::vector < std::vector <int> > m_voxelGrid;

        glm::vec3 m_pos_min;
        glm::vec3 m_pos_max;
        CaracParticle m_carac;
        Material m_mat;

        bool m_once_update = false;


        void m_create_particles (int nb_particles_per_side);
        void m_create_particles_center (int nb_particles);
        void m_create_voxelGrid ();

        void m_particles_collisions ();
        // void resolve_collision (Particle* p1, Particle* p2);
        bool is_in_collision (Particle p1, Particle p2);



};