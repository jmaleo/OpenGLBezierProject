#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include "structures.hpp"

class Particle {

    public:

        // Constructeur pour initialiser les paramètres de la particule
        Particle(CaracParticle carac, Material mat) {
            m_carac = carac;
            m_mat = mat;
        }

        // Vérifier si la particule est encore en vie
        bool is_alive() {
            return m_carac.life > 0.0f;
        }

        void update() { m_carac = m_carac_temp; }

        // getters 
        Material* get_material() { return &m_mat; }
        CaracParticle* get_carac() { return &m_carac; }

        // setters
        void set_material(Material mat) { m_mat = mat; }
        void set_carac(CaracParticle carac) { m_carac = carac; }

        void set_carac_temp(CaracParticle carac) { m_carac_temp = carac; }

    private : 

        CaracParticle m_carac;
        CaracParticle m_carac_temp;
        Material m_mat;

};      