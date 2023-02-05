#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>

// VecType like glm::vec2 or glm::vec3
template<typename VecType>
class MyObject{

    public : 
        MyObject () {
            std::cout << "J'ai enregistrer mon objet" << std::endl;
        }
        
        virtual ~MyObject ();

        // // //
        // SETTERS
        // // //

        void setVertices ( std::vector < VecType > list_vertices );

        void setNormales ( std::vector < VecType > list_normales);

        void setColors ( std::vector < glm::vec4 > list_colors);
        
        void setIndices ( std::vector < int > list_indices ) { m_indices = list_indices; }


        // // //
        // GETTERS
        // // //

        std::vector < VecType > getVertices () { return m_vertices; }
        
        std::vector < VecType > getNormales () { return m_normales; }
        
        std::vector < int > getIndices () { return m_indices; }

        std::vector < glm::vec4 > getColors () { return m_colors; }

    private : 
        int m_nb_vertices = 0;
        std::vector < VecType > m_vertices;
        std::vector < VecType > m_normales;
        std::vector <glm::vec4 > m_colors;
        std::vector < int > m_indices;


};