#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>

struct s_material {
    glm::vec3 color = glm::vec3(0.0f);
    float metallic = 0.3f;
    float roughness = 0.8f;
    float ao = 0.5f;
}typedef Material;

Material initialiseMaterial (){
    Material mat;
    mat.color = glm::vec3(0.2f);
    mat.metallic = 0.8f;
    mat.roughness = 0.2f;
    mat.ao = 0.5f;
    return mat;
}

// VecType like glm::vec2 or glm::vec3
template<typename VecType>
class MyObject{

    public : 
        MyObject ( int id ) { m_id = id; }
        MyObject ( int id, std::vector < VecType > list_vertices, std::vector < VecType > list_normales, glm::vec3 color, std::vector < unsigned int > list_indices );
        MyObject ( int id, std::vector < VecType > list_vertices, std::vector < unsigned int > list_indices );

        virtual ~MyObject ();

        // // //
        // SETTERS
        // // //
        void setId (int id) { m_id = id; }

        void setVertices ( std::vector < VecType > list_vertices );

        void setNormales ( std::vector < VecType > list_normales );

        void setColor ( glm::vec3 color );

        void setMaterial (Material mat) { m_mat = mat; }
        
        void setIndices ( std::vector < unsigned int > list_indices ) { m_indices = list_indices; }


        // // //
        // GETTERS
        // // //
        int getId () { return m_id; }

        std::vector < VecType > getVertices () { return m_vertices; }
        
        std::vector < VecType > getNormales () { return m_normales; }
        
        std::vector < unsigned int > getIndices () { return m_indices; }

        Material* getMaterial () { return &m_mat; }

        unsigned int* get_VAO () { return &VAO; };

        unsigned int* get_VBOvertices () { return &VBOvertices; };

        unsigned int* get_VBOnormales () { return &VBOnormales; };

        unsigned int* get_EBO () { return &EBO; };

    private : 
        int m_id = -1;
        int m_nb_vertices = 0;
        float m_depth = 0;
        float m_width = 0;
        float m_height = 0;
        unsigned int VAO, VBOvertices, VBOnormales, EBO;
        std::vector < VecType > m_vertices;
        std::vector < VecType > m_normales;
        std::vector < unsigned int > m_indices;


        // Parametres de matériaux
        glm::vec3 m_color; // Albedo
        Material m_mat;


};