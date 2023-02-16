#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>


template<typename VecType>
class Light {
    public :
        Light (int id, VecType position, glm::vec3 color) {
            m_id = id;
            m_pos = position;
            m_col = color;
        }

        // getter
        int getId () { return m_id; }

        VecType getPosition () { return m_pos; }
        
        glm::vec3 getColor () { return m_col; }

        unsigned int* get_VAO() { return &VAO; }

        unsigned int* get_VBOposition() { return &VBOposition; }

        // Setter 
        void setId (int id) { m_id = id; }

        void setPosition (VecType position) { m_pos = position; }

        void setColor (VecType color) { m_col = color; }

    private :
        int m_id = -1;
        VecType m_pos;
        glm::vec3 m_col;

        unsigned int VAO, VBOposition;
};
