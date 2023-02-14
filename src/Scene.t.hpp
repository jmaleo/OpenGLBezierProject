#pragma once

#include "_Scene.hpp"

/**
 * @brief Destroy the Scene:: Scene object
 * TODO
 * 
 * @tparam VecType 
 */
template<typename VecType>
Scene<VecType>::~Scene(){
    m_cam = nullptr;
    m_listLights.clear();
    m_listObjects.clear();
    m_numObj = 0;
    delete this;
}

/**
 * @brief 
 * TODO
 * 
 * @tparam VecType 
 * @param obj 
 * @param id 
 */
template<typename VecType>
void Scene<VecType>::addObject (MyObject<VecType>* obj){
    m_listObjects.push_back(obj);
}

/**
 * @brief 
 * TODO
 * 
 * @tparam VecType 
 * @param id 
 */
template<typename VecType>
void Scene<VecType>::deleteObject (int id){
    for ( int i = 0; i < m_listObjects.size(); i++ ){
        if (m_listObjects.at(i)->getId() == id){
            m_listObjects.erase(i);
            return;
        }
    }
}

/**
 * @brief 
 * TODO
 * 
 * @tparam VecType 
 * @param obj 
 * @param id 
 */
template<typename VecType>
void Scene<VecType>::addLight (Light<VecType>* light){
    m_listLights.push_back(light);
}

/**
 * @brief 
 * TODO
 * 
 * @tparam VecType 
 * @param id 
 */
template<typename VecType>
void Scene<VecType>::deleteLight (int id){
    for ( int i = 0; i < m_listLights.size(); i++ ){
        if (m_listLights.at(i)->getId() == id){
            m_listLights.erase(i);
            return;
        }
    }
}


/**
 * @brief 
 * 
 * TODO
 * @tparam VecType 
 */
template<typename VecType>
void Scene<VecType>::cleanScene (){
    return;
}