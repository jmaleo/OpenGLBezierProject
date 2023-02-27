#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include "structures.hpp"
#include "ParticlesContainer.t.hpp"

// VecType like glm::vec2 or glm::vec3 
// FOR THE MOMENT, THIS CLASS IS ONLY FOR CUBE (3D). Maybe, it could be interesting to make it generic for all kind of object and implements sub classes for each kind of object.
template<typename VecType>
class Object{

    public : 
        Object ( int id ) { m_id = id; }
        Object ( int id, std::vector < VecType > list_vertices, std::vector < VecType > list_normales, glm::vec3 color, std::vector < unsigned int > list_indices );
        Object ( int id, std::vector < VecType > list_vertices, std::vector < unsigned int > list_indices );

        virtual ~Object ();

        // // //
        // SETTERS
        // // //

        void setType (int type) { m_type = type; }

        void setId (int id) { m_id = id; }

        void setVertices ( std::vector < VecType > list_vertices );

        void setNormales ( std::vector < VecType > list_normales );

        void setColor ( glm::vec3 color );

        void setMaterial (Material mat) { m_mat = mat; }
        
        void setIndices ( std::vector < unsigned int > list_indices ) { m_indices = list_indices; }

        void setMinPosition ( VecType minPosition ) { m_minPosition = minPosition; }

        void setMaxPosition ( VecType maxPosition ) { m_maxPosition = maxPosition; }

        // // //
        // GETTERS
        // // //
        VecType getMinPosition () { return m_minPosition; }

        VecType getMaxPosition () { return m_maxPosition; }
        
        int getId () { return m_id; }

        int getType () { return m_type; }

        std::vector < VecType > getVertices () { return m_vertices; }
        
        std::vector < VecType > getNormales () { return m_normales; }
        
        std::vector < unsigned int > getIndices () { return m_indices; }

        Material* getMaterial () { return &m_mat; }

        unsigned int* get_VAO () { return &VAO; };

        unsigned int* get_VBOvertices () { return &VBOvertices; };

        unsigned int* get_VBOnormales () { return &VBOnormales; };

        unsigned int* get_EBO () { return &EBO; };



        bool isContainer () { return !(m_container == nullptr); }
        ParticlesContainer* getContainer () { return m_container; }
        void setContainer (ParticlesContainer* container) { m_container = container; }


    private : 
        // 0 for cube, 1 for other;
        int m_type = 0;
        int m_id = -1;
        int m_nb_vertices = 0;
        float m_depth = 0;
        float m_width = 0;
        float m_height = 0;
        unsigned int VAO, VBOvertices, VBOnormales, EBO;
        std::vector < VecType > m_vertices;
        std::vector < VecType > m_normales;
        std::vector < unsigned int > m_indices;

        VecType m_minPosition = VecType(0.0f);
        VecType m_maxPosition = VecType(0.0f);

        // Parametres de matériaux
        Material m_mat;

        // Particles container
        ParticlesContainer* m_container = nullptr;



};