#pragma once

#include "_Render_scene.hpp"

template<typename VecType>
RenderScene<VecType>::RenderScene(Scene<VecType>* scene) { 
    m_myScene = scene; 
    initGLSL();
    initShaders();
    m_render = new Render<VecType> (scene->getCamera());
}

template<typename VecType>
void RenderScene<VecType>::setUp(float src_width, float src_height){
    // m_render->setUp_FBO(src_width, src_height);
    m_render->setUp_BLOOM(src_width, src_height);
    m_render->setUp_quad();
    
    m_setUpLights();
    m_setUpObjects();
}

/**
 * I NEED TO CHANGE THIS FUNCTION TO TAKE INTO ACCOUNT GOOD SHADER PROGRAMS / Movement
 */
template<typename VecType>
void RenderScene<VecType>::m_setUpObjects(){
    std::vector <Object<VecType>*> objs = m_myScene->getListObjects();
    for (auto obj : objs){
        m_render->setUp_Object(obj);
    }
} 

template<typename VecType>
void RenderScene<VecType>::m_setUpLights(){
    std::vector <Light<VecType>*> lights = m_myScene->getListLights();
    for (auto light : lights){
        m_render->setUp_Light(light);
    }
} 

/**
 * @brief Does all the draw process.
 * @param selection : 1 for only objects, 2 for only lights and 3 for both. Else : nothing
 */
template<typename VecType>
void RenderScene<VecType>::draw (float width, float height, int selection){

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Bind le frame buffer de base
    m_render->bind_HDR();

    // Be Carreful, into the drawObject function, we take into account the particles.
    switch (selection){ // Rendre les objets
        case (1) :
            m_drawObjects(width, height);
            break;
        case (2) :
            m_drawLights(width, height);
            break;
        case (3) :
            m_drawObjects(width, height);
            m_drawLights(width, height);
            break;
        default : break;
    }
    m_draw_new(width, height, selection);
    
    // m_render->unbind_HDR();
    // std::cout << "Draw error : " << glGetError() << std::endl;

    // BLUR THE FRAME BUFFER
    m_render->blur (m_shaderBlur, (unsigned int) width, (unsigned int) height, 10);

    // Only hdr
    // m_render->draw_HDR(m_shaderHDR, width, height, (int16_t)m_hdr, m_exposure);
    
    // Effectuer le rendu HDR avec BLOOM;
    m_render->draw_BLOOM (m_shaderBloom, width, height, (int16_t)m_hdr, m_exposure, (int16_t)m_bloom, m_onlyBright);
}


template<typename VecType>
void RenderScene<VecType>::m_drawObjects(float width, float height){
    std::vector <Object<VecType>*> objs = m_myScene->getListObjects();
    std::vector <Light<VecType>*> lights = m_myScene->getListLights();    

    for (auto obj : objs){
        if (!m_selected_object || m_selected != obj->getId()){
            m_render->draw_Object(obj, lights, m_shaderObj, width, height);
        }
        if (obj->isContainer() && m_particlesVisible){
            if (obj->getContainer()->get_number_particles() == 0){
                m_render->draw_Object(obj, lights, m_shaderObj, width, height);
            }
            else {
                if (! m_stopParticles)
                    obj->getContainer()->update(m_deltaTime);
                m_render->draw_Particles(obj, m_shaderLight, width, height);
            }
        }
    }
    if (m_selected_object){
        m_drawObjSelection(m_selected, width, height);
    }
} 

template<typename VecType>
void RenderScene<VecType>::m_drawLights(float width, float height){
    std::vector <Light<VecType>*> lights = m_myScene->getListLights();
    for (auto light : lights){
        if (!m_selected_light || m_selected != light->getId())
            m_render->draw_Light(light, m_shaderLight, width, height);
    }
    if (m_selected_light){
        m_drawLightSelection(m_selected, width, height);
    }

} 

template<typename VecType>
void RenderScene<VecType>::m_drawObjSelection (int id, float width, float height){
    std::vector <Object<VecType>*> objs = m_myScene->getListObjects();
    std::vector <Light<VecType>*> lights = m_myScene->getListLights();
    for (auto obj : objs){
        if (obj->getId() == id){
            m_render->draw_Object_Selected(obj, lights, m_shaderObj, width, height);
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
    return nullptr;
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
    return glm::vec3(0.0f);
}

template<typename VecType>
void RenderScene<VecType>::setLightColor(int id, float* color){
    for (auto light : m_myScene->getListLights()){
        if (light->getId() == id){
            return light->setColor(glm::vec3(color[0], color[1], color[2]));
        }
    }
}

template<typename VecType>
void RenderScene<VecType>::addLight (){
    int nbLight = m_myScene->getListLights().size();
    changeNumberLight(m_path_fragmentShader, nbLight, nbLight+1 );
    m_myScene->addLight(m_temp_light);
    std::cout << "nb Light before " << nbLight << " and after : " << m_myScene->getListLights().size() << std::endl;
    // changeNumberLight(SHADER_DIR+std::string("fragmentShader.glsl"), 4, 5);
}
/**
 * @param selection : 1 for only objects, 2 for only lights and 3 for both. Else : nothing
 */
template<typename VecType>
void RenderScene<VecType>::m_draw_new(float width, float height, int selection){
    if (m_temp_light != nullptr && (selection == 2 || selection == 3)){
        m_render->setUp_Light(m_temp_light);
        m_render->draw_Light_Selected(m_temp_light, m_shaderLight, width, height);
    }
    else {
        if (m_temp_object != nullptr && (selection == 1 || selection == 3)){
            m_render->setUp_Object(m_temp_object);
            m_render->draw_Object_Selected(m_temp_object, m_myScene->getListLights(), m_shaderObj, width, height);
        }
    }
}

template<typename VecType>
void RenderScene<VecType>::resetGLSL(){
    int nbLight = m_myScene->getListLights().size();
    changeNumberLight(m_path_fragmentShader, nbLight, 1 );
}

template<typename VecType>
void RenderScene<VecType>::initGLSL(){
    int nbLight = m_myScene->getListLights().size();
    changeNumberLight(m_path_fragmentShader, 1, nbLight );
}

template<typename VecType>
void RenderScene<VecType>::initShaders(){
    m_shaderObj = new ShaderProgram(m_path_vertexShader.c_str(), m_path_fragmentShader.c_str());

    m_shaderLight = new ShaderProgram(m_path_vertexShaderLight.c_str(), m_path_fragmentShaderLight.c_str());

    m_shaderHDR = new ShaderProgram(m_path_vertexShaderHDR.c_str(), m_path_fragmentShaderHDR.c_str());

    m_shaderBloom = new ShaderProgram(m_path_vertexShaderBloom.c_str(), m_path_fragmentShaderBloom.c_str());

    m_shaderBlur = new ShaderProgram(m_path_vertexShaderBlur.c_str(), m_path_fragmentShaderBlur.c_str());


    m_shaderBlur->use();
    m_shaderBlur->setInt("image", 0);
    
    m_shaderBloom->use();
    m_shaderBloom->setInt("hdrBuffer", 0);
    m_shaderBloom->setInt("bloomBlur", 1);
    m_shaderBloom->setInt("brightPixels", 2);
}


// Position : 1 for uniform disposition and 0 for the center.
template<typename VecType>
void RenderScene<VecType>::resetParticles(int nbParticles, int position){
    for (auto obj : m_myScene->getListObjects()){
        if (obj->isContainer()){
            // I take the number of wanted particles, and I took the pow of 1/3 in order to have particles per side.
            obj->getContainer()->resetParticles(pow(nbParticles, 1.f/3.f), position);
            obj->getContainer()->set_setUp(false);
            std::cout << "Reset particles" << std::endl;
        }
    }
}

template<typename VecType>
bool RenderScene<VecType>::isContainer(int id){
    for (auto obj : m_myScene->getListObjects()){
        if (obj->getId() == id){
            return obj->isContainer();
        }
    }
    return false;
}

template<typename VecType>
VecType RenderScene<VecType>::getPosition(int id, bool obj){
    if (obj){
        for (auto obj : m_myScene->getListObjects()){
            if (obj->getId() == id){
                return obj->getMinPosition();
            }
        }
    }
    else {
        for (auto light : m_myScene->getListLights()){
            if (light->getId() == id){
                return light->getPosition();
            }
        }
    }
    return VecType(0.0f);
}

template<typename VecType>
void RenderScene<VecType>::setObjPosition(int id, VecType pos){
    for (auto obj : m_myScene->getListObjects()){
        if (obj->getId() == id){
            glm::vec3 min_pos = obj->getMinPosition();
            glm::vec3 translation = pos - min_pos;
            obj->translate(translation);
            obj->setMaxPosition(obj->getVertices()[5]);
            obj->setMinPosition(obj->getVertices()[3]);
            m_render->setUp_Object(obj);
        }
    }
}

template<typename VecType>
void RenderScene<VecType>::setLightPosition(int id, VecType pos){
    for (auto light : m_myScene->getListLights()){
        if (light->getId() == id){
            glm::vec3 min_pos = light->getPosition();
            glm::vec3 translation = pos - min_pos;
            light->translate(translation);
            m_render->setUp_Light(light);
        }
    }
}