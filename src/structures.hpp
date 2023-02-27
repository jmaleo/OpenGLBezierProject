#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef struct s_particle {
    glm::vec3 position = glm::vec3(0.0f); // Position de la particule dans l'espace 3D
    glm::vec3 velocity = glm::vec3(0.0f, -0.1f, 0.0f);  // Vitesse de la particule
    glm::vec3 acceleration = glm::vec3 (0.0f);   // Accélération de la particule
    float life;     // Durée de vie de la particule en secondes
    float size; // Taille de la particule
    float mass; // Masse de la particule
} CaracParticle;

typedef struct s_material {
    glm::vec3 color = glm::vec3(0.0f);
    float metallic = 0.3f;
    float roughness = 0.8f;
    float ao = 0.5f;
} Material;


Material initialiseMaterial (){
    Material mat;
    mat.color = glm::vec3(0.2f);
    mat.metallic = 0.8f;
    mat.roughness = 0.2f;
    mat.ao = 0.5f;
    return mat;
}

CaracParticle initialiseCaracParticle (){
    CaracParticle carac;
    carac.position = glm::vec3(0.0f);
    carac.velocity = glm::vec3(0.0f, -0.1f, 0.0f);
    carac.acceleration = glm::vec3(0.0f, 9.81f, 0.0f);
    carac.life = 1000.0f;
    carac.size = 0.1f;
    carac.mass = 1.0f;
    return carac;
}