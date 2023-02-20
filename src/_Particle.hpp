#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include "Object.t.hpp"

class Particle {

    public:

        // Constructeur pour initialiser les paramètres de la particule
        Particle(glm::vec3 position, glm::vec3 color, glm::vec3 velocity, glm::vec3 acceleration, float life, float size) {
            this->m_position = position;
            this->m_velocity = velocity;
            this->m_acceleration = acceleration;
            this->m_life = life;
            this->m_size = size;
            m_mat.ao = 0.5f;
            m_mat.metallic = 0.8f;
            m_mat.roughness = 0.2f;
            m_mat.color = color;
        }

        // Vérifier si la particule est encore en vie
        bool is_alive() {
            return m_life > 0.0f;
        }

        // getters 
        glm::vec3 get_position() { return m_position; }
        glm::vec3 get_velocity() { return m_velocity; }
        glm::vec3 get_acceleration() { return m_acceleration; }
        float get_life() { return m_life; }
        float get_size() { return m_size; }
        Material* get_material() { return &m_mat; }
        float get_mass() { return m_mass; }

        // setters
        void set_position(glm::vec3 position) { this->m_position = position; }
        void set_velocity(glm::vec3 velocity) { this->m_velocity = velocity; }
        void set_acceleration(glm::vec3 acceleration) { this->m_acceleration = acceleration; }
        void set_life(float life) { this->m_life = life; }
        void set_size(float size) { this->m_size = size; }
        void set_mass(float mass) { this->m_mass = mass; }


    private : 
    
        glm::vec3 m_position; // Position de la particule dans l'espace 3D
        glm::vec3 m_velocity; // Vitesse de la particule
        glm::vec3 m_acceleration; // Accélération de la particule
        float m_life; // Durée de vie de la particule en secondes
        float m_size; // Taille de la particule
        float m_mass = 1; // Masse de la particule
        Material m_mat;

};      