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
        if (!m_selected_object || m_selected != obj->getId())
            m_render->draw_Object(obj, lights, m_shaderObj_microfacette, width, height);
            // m_render->draw_Object(obj, lights, m_shaderObj, width, height);
    }
    if (m_selected_object)
        m_drawObjSelection(m_selected, width, height);
} 

template<typename VecType>
void RenderScene<VecType>::drawLights(float width, float height){
    std::vector <Light<VecType>*> lights = m_myScene->getListLights();
    for (auto light : lights){
        if (!m_selected_light || m_selected != light->getId())
            m_render->draw_Light(light, m_shaderLight, width, height);
    }
    if (m_selected_light)
        m_drawLightSelection(m_selected, width, height);

} 

template<typename VecType>
void RenderScene<VecType>::m_drawObjSelection (int id, float width, float height){
    std::vector <MyObject<VecType>*> objs = m_myScene->getListObjects();
    std::vector <Light<VecType>*> lights = m_myScene->getListLights();
    for (auto obj : objs){
        if (obj->getId() == id){
            m_render->draw_Object_Selected(obj, lights, m_shaderObj_microfacette, width, height);
            // m_render->draw_Object_Selected(obj, lights, m_shaderObj, width, height);
            return;
        }
    }
}

template<typename VecType>
void RenderScene<VecType>::m_drawLightSelection (int id, float width, float height){
    std::vector <Light<VecType>*> lights = m_myScene->getListLights();
    for (auto light : lights){
        if (light->getId() == id){
            m_render->draw_Light_Selected(light, m_shaderLight, width, height);
            return;
        }
    }
}

template<typename VecType>
std::vector <int> RenderScene<VecType>::getObjectIds (){
    std::vector <int> ids;
    for (auto obj : m_myScene->getListObjects()){
        ids.push_back(obj->getId());
    }
    return ids;
}

template<typename VecType>
std::vector <int> RenderScene<VecType>::getLightIds (){
    std::vector <int> ids;
    for (auto light : m_myScene->getListLights()){
        ids.push_back(light->getId());
    }
    return ids;
}

template<typename VecType>
void RenderScene<VecType>::setObjectSelected(int id){
    if (id == -1){
        m_selected = -1;
        m_selected_object = false;
    }
    else {
        m_selected = id;
        m_selected_object = true;
        m_selected_light = false;
    }
}

template<typename VecType>
void RenderScene<VecType>::setLightSelected(int id){
    if (id == -1){
        m_selected = -1;
        m_selected_light = false;
    }
    else {
        m_selected = id;
        m_selected_light = true;
        m_selected_object = false;
    }
}

template<typename VecType>
Material* RenderScene<VecType>::getMaterial(int id){
    for (auto obj : m_myScene->getListObjects()){
        if (obj->getId() == id){
            return obj->getMaterial();
        }
    }
}

template<typename VecType>
void RenderScene<VecType>::setMaterial(int id, Material mat){
    for (auto obj : m_myScene->getListObjects()){
        if (obj->getId() == id){
            return obj->setMaterial(mat);
        }
    }
}

template<typename VecType>
glm::vec3 RenderScene<VecType>::getLightColor(int id){
    for (auto light : m_myScene->getListLights()){
        if (light->getId() == id){
            return light->getColor();
        }
    }
}

template<typename VecType>
void RenderScene<VecType>::setLightColor(int id, float* color){
    for (auto light : m_myScene->getListLights()){
        if (light->getId() == id){
            return light->setColor(glm::vec3(color[0], color[1], color[2]));
        }
    }
}