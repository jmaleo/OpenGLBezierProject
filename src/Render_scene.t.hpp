#pragma once

#include "_Render_scene.hpp"

template<typename VecType>
RenderScene<VecType>::RenderScene(Scene<VecType>* scene) { 
    m_myScene = scene; 
    m_render = new Render<VecType> (scene->getCamera());
}

/**
 * I NEED TO CHANGE THIS FUNCTION TO TAKE INTO ACCOUNT GOOD SHADER PROGRAMS 
 */
template<typename VecType>
void RenderScene<VecType>::setUpObjects(){
    std::vector <MyObject<VecType>*> objs = m_myScene->getListObjects();
    for (auto obj : objs){
        m_render->setUp_Object(obj);
    }
} 

template<typename VecType>
void RenderScene<VecType>::setUpLights(){
    std::vector <Light<VecType>*> lights = m_myScene->getListLights();
    for (auto light : lights){
        m_render->setUp_Light(light);
    }
} 

template<typename VecType>
void RenderScene<VecType>::drawObjects(float width, float height){
    std::vector <MyObject<VecType>*> objs = m_myScene->getListObjects();
    std::vector <Light<VecType>*> lights = m_myScene->getListLights();
    for (auto obj : objs){
        // m_render->draw_Object(obj, m_shaderControl, width, height);
        m_render->draw_Object(obj, lights, m_shaderTest, width, height);
    }
} 

template<typename VecType>
void RenderScene<VecType>::drawLights(float width, float height){
    std::vector <Light<VecType>*> lights = m_myScene->getListLights();
    for (auto light : lights){
        m_render->draw_Light(light, m_shaderLight, width, height);
    }
} 
