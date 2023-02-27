#include "_Interface.hpp"

/**
 * @brief 
 * TODO
 * 
 * @tparam VecType 
 */
template<typename VecType>
void ImGuiInterface<VecType>::draw(float width, float height){
    _drawInterface();
    _drawScene();
    _drawObject();
    _drawLights();
    _drawSelectInformation();
    _drawNewInformation(width, height);

    _drawFrame(width, height);

}

/**
 * @brief 
 * TODO
 * 
 * @tparam VecType 
 */
template <typename VecType>
void ImGuiInterface<VecType>::quit (){
    m_renderScene->resetGLSL();
}

/**
 * @brief 
 * TODO
 * 
 * @tparam VecType 
 */
template <typename VecType>
void ImGuiInterface<VecType>::_drawInterface(){

    m_begin_win = m_size_offset;

    ImGui::SetNextWindowPos( ImVec2( m_begin_win, m_size_offset ) );
    ImGui::SetNextWindowSize( ImVec2( m_size_width, 0) );
    ImGui::Begin("Test_Interface", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    // ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    ImGui::Text("Principale fenêtre de l'interface, ET OUI.");

    if ( ImGui::Button ( "Show Scene" ) ){
        if (m_scene_visible) {
            m_objects_visible = false;
            m_lights_visible = false;
        }
        m_scene_visible = ! m_scene_visible;
    }
    ImGui::End();
}
/**
 * @brief 
 * TODO
 * 
 */
template<typename VecType>
void ImGuiInterface<VecType>::_drawScene(){
    if ( !m_scene_visible ){ 
        return;
    }

    m_begin_win += (m_size_width + m_size_offset);

    ImGui::SetNextWindowPos( ImVec2( m_begin_win, m_size_offset ) );
    ImGui::SetNextWindowSize( ImVec2( m_size_width, 0) );
    ImGui::Begin("Test_Interface_SCENE", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    if ( ImGui::Button ("Hdr") ){
        m_hdr = !m_hdr;
        m_renderScene->setHDR(m_hdr);
    }
    ImGui::SameLine();
    ImGui::Text((m_hdr ?"On":"Off"));

    ImGui::SliderFloat("Exposure", m_renderScene->getExposure(), 0.1f, 10.0f);

    if ( ImGui::Button ("Bloom") ){
        m_bloom = !m_bloom;
        m_renderScene->setBloom(m_bloom);
    }
    ImGui::SameLine();
    ImGui::Text((m_bloom ?"On":"Off"));

    if ( ImGui::Button ("OnlyBright") ){
        m_onlyBright = !m_onlyBright;
        m_renderScene->setOnlyBright(m_onlyBright);
    }
    ImGui::SameLine();
    ImGui::Text((m_onlyBright ?"On":"Off"));

    if ( ImGui::Button ( "Show objects") ) {
        m_objects_visible = ! m_objects_visible;
    }

    if ( ImGui::Button ( "Show lights" ) ) {
        m_lights_visible = ! m_lights_visible;
    }

    ImGui::End();

}

/**
 * @brief 
 * TODO
 * 
 */
template<typename VecType>
void ImGuiInterface<VecType>::_drawObject(){
    if ( !m_objects_visible ) return;

    m_begin_win += (m_size_width + m_size_offset);

    std::vector <int> ids = m_renderScene->getObjectIds();

    ImGui::SetNextWindowPos( ImVec2( m_begin_win, m_size_offset ) );
    ImGui::SetNextWindowSize( ImVec2( m_size_width, 0) );
    ImGui::Begin("Test_Interface_OBJECTS", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    for (int id : ids){
        if (!m_selected_object || m_selected != id){
            std::string button_name = "Object " + std::to_string(id);
            if (ImGui::Button((button_name).c_str())){
                m_selected = id;
                m_selected_object = true;
                m_selected_light = false;
                m_renderScene->setObjectSelected (m_selected);
            }
        }
        if (m_selected_object && m_selected == id){
            if (ImGui::Button(("Unselect Object " + std::to_string(id)).c_str())){
                m_selected = -1;
                m_selected_object = false;
                m_renderScene->setObjectSelected(-1);
            }  
        }
    }

    ImGui::Separator();

    if ( ImGui::Button ( "Add Object" ) ) {
        glm::vec3 camPos = m_renderScene->getCameraPosition();
        m_renderScene->setTempObject(nullptr);
        m_newThing = true;
        m_renderScene->setTempLight(nullptr);
    }

    ImGui::End();

}

/**
 * @brief 
 * TODO
 * 
 */
template<typename VecType>
void ImGuiInterface<VecType>::_drawLights(){
    if ( !m_lights_visible ) return;

    m_begin_win += (m_size_width + m_size_offset);

    std::vector <int> ids = m_renderScene->getLightIds();

    ImGui::SetNextWindowPos( ImVec2( m_begin_win, m_size_offset ) );
    ImGui::SetNextWindowSize( ImVec2( m_size_width, 0) );
    ImGui::Begin("Test_Interface_LIGHTS", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    for (int id : ids){
        if (!m_selected_light || m_selected != id){
            std::string button_name = "Light " + std::to_string(id);
            if (ImGui::Button(button_name.c_str())){
                m_selected = id;
                m_selected_light = true;
                m_selected_object = false;
                m_renderScene->setLightSelected (m_selected);
            }
        }
        if (m_selected_light && m_selected == id){
            if (ImGui::Button(("Unselect Light " + std::to_string(id)).c_str())){
                m_selected = -1;
                m_selected_light = false;
                m_renderScene->setLightSelected(-1);
            }  
        }
    }

    ImGui::Separator();

    if ( ImGui::Button ( "Add Light" ) ) {
        glm::vec3 camPos = m_renderScene->getCameraPosition();
        glm::vec3 position = glm::vec3 (camPos[0], camPos[1], camPos[2] - 10);
        m_renderScene->setTempLight(new Light<VecType>(-10, position, glm::vec3(0.6f, 0.6f, 0.6f)));
        m_renderScene->setTempObject(nullptr);
        m_newThing = true;
        first_position = position;
    }

    ImGui::End();
}

template<typename VecType>
void ImGuiInterface<VecType>::_drawFrame(float width, float height){
    if (!m_scene_visible){ return; }

    int obj = (m_objects_visible)?1:0;
    int lig = (m_lights_visible)?1:0;
    int selection = obj + 2 * lig;
    m_renderScene->draw(width, height, selection);
}

// glm::vec3 color = glm::vec3(0.0f);
// float metallic = 0.3f;
// float roughness = 0.8f;
// float ao = 0.5f;

template<typename VecType>
void ImGuiInterface<VecType>::_drawSelectInformation(){
    if (m_selected == -1) {
        m_selected_mat = nullptr;
        return; 
    }

    ImGui::Begin("Informations");

    if (m_selected_object){
        m_selected_mat = m_renderScene->getMaterial(m_selected);
        if (m_selected_mat == nullptr){
            std::cout << "Material not found" << std::endl;
            exit(1);
        } 
        float color[3] = {m_selected_mat->color[0], m_selected_mat->color[1], m_selected_mat->color[2] };

        ImGui::ColorEdit3 ("Color", color);
        ImGui::SliderFloat ("metallic", &(m_selected_mat->metallic), 0.0f, 1.0f);
        ImGui::SliderFloat ("roughness", &(m_selected_mat->roughness), 0.0f, 1.0f);
        ImGui::SliderFloat ("ao", &(m_selected_mat->ao), 0.0f, 1.0f);

        m_selected_mat->color = glm::vec3(color[0], color[1], color[2]);
    }

    if (m_selected_light){
        glm::vec3 light_color = m_renderScene->getLightColor(m_selected);
        float color[3] = {light_color[0], light_color[1], light_color[2] };
        ImGui::ColorEdit3 ("Color", color);
        m_renderScene->setLightColor(m_selected, color);
    }


    ImGui::End();
}

template<typename VecType>
void ImGuiInterface<VecType>::_drawNewInformation(float width, float height){
    if (!m_newThing) {
        return;
    }

    ImGui::Begin("New thing");

    Object<VecType>* o = m_renderScene->getTempObject();
    Light<VecType>* l = m_renderScene->getTempLight();

    if (o != nullptr){
        m_selected_mat = m_renderScene->getMaterial(m_selected);
        float color[3] = {m_selected_mat->color[0], m_selected_mat->color[1], m_selected_mat->color[2] };

        ImGui::ColorEdit3 ("Color", color);
        ImGui::SliderFloat ("metallic", &(m_selected_mat->metallic), 0.0f, 1.0f);
        ImGui::SliderFloat ("roughness", &(m_selected_mat->roughness), 0.0f, 1.0f);
        ImGui::SliderFloat ("ao", &(m_selected_mat->ao), 0.0f, 1.0f);

        m_selected_mat->color = glm::vec3(color[0], color[1], color[2]);
    }

    if (l != nullptr){
        glm::vec3 light_color = l->getColor();
        float color[3] = {light_color[0], light_color[1], light_color[2] };
        ImGui::ColorEdit3 ("Color", color);
        l->setColor(glm::vec3(color[0], color[1], color[2]));
        glm::vec3 position = l->getPosition();
        ImGui::SliderFloat("X", &(position[0]), first_position[0]-10.0f, first_position[0]+10.0f );
        ImGui::SliderFloat("Y", &(position[1]), first_position[1]-10.0f, first_position[1]+10.0f );
        ImGui::SliderFloat("Z", &(position[2]), first_position[2]-10.0f, first_position[2]+10.0f );
        l->setPosition(position);
        if ( ImGui::Button ("Add it !")) {
            m_renderScene->addLight();
            m_renderScene->initShaders();
            m_renderScene->setUp(width, height);
            m_renderScene->setTempLight(nullptr);
            m_renderScene->setTempObject(nullptr);
            m_newThing = false;
        }
        if ( ImGui::Button (" Revert ")){
            m_renderScene->setTempLight(nullptr);
            m_renderScene->setTempObject(nullptr);
            m_newThing = false;
        }
    }


    ImGui::End();
}