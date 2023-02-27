#pragma once
#include "_Object.hpp"

/**
 * @brief Constructor.
 * 
 * @tparam VecType 
 */
template<typename VecType>
Object<VecType>::Object ( int id,  std::vector < VecType > list_vertices, 
    std::vector < VecType > list_normales, 
        glm::vec3 color, 
            std::vector < unsigned int > list_indices ){
    m_id = id;
    m_mat = initialiseMaterial();
    setVertices(list_vertices);
    setNormales(list_normales);
    setColor(color);
    setIndices(list_indices);


    m_depth = glm::distance(list_vertices[4], list_vertices[1]);
    m_width = glm::distance(list_vertices[2], list_vertices[14]);
    m_height = glm::distance(list_vertices[2], list_vertices[11]);
}

template<typename VecType>
Object<VecType>::Object ( int id, std::vector < VecType > list_vertices, std::vector < unsigned int > list_indices ){
    
    m_id = id;
    setVertices(list_vertices);
    setIndices(list_indices);
    
    m_mat = initialiseMaterial();

    m_depth = glm::distance(list_vertices[4], list_vertices[1]);
    m_width = glm::distance(list_vertices[2], list_vertices[14]);
    m_height = glm::distance(list_vertices[2], list_vertices[11]);
}

/**
 * @brief Destroy the My Object< Vec Type>:: My Object object
 * 
 * @tparam VecType 
 */
template<typename VecType>
Object<VecType>::~Object(){
    m_vertices.clear();
    m_indices.clear();
    m_normales.clear();
    m_nb_vertices = 0;
}

/**
 * @brief set the vertices of my object.
 * 
 * @tparam VecType 
 * @param list_vertices 
 */
template <typename VecType>
void Object<VecType>::setVertices ( std::vector < VecType > list_vertices ){
    m_vertices = list_vertices;
    m_nb_vertices = m_vertices.size();
}

/**
 * @brief Set the normales of my object
 * 
 * @tparam VecType 
 * @param list_normales 
 */
template <typename VecType>
void Object<VecType>::setNormales( std::vector < VecType > list_normales ){
    if ( list_normales.size() != m_nb_vertices ) {
        std::cerr << "You can't add a list of normales for a different number of vertices." << std::endl;
        return;
    }
    m_normales = list_normales;
}

/**
 * @brief Set the colors of my object
 * 
 * @tparam VecType 
 * @param list_colors 
 */
template <typename VecType>
void Object<VecType>::setColor( glm::vec3 color ){
    m_mat.color = color;
}

