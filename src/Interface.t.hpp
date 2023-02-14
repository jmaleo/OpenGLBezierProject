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

    _drawFrame(width, height);
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
    if ( !m_scene_visible ) return;

    m_begin_win += (m_size_width + m_size_offset);

    ImGui::SetNextWindowPos( ImVec2( m_begin_win, m_size_offset ) );
    ImGui::SetNextWindowSize( ImVec2( m_size_width, 0) );
    ImGui::Begin("Test_Interface_SCENE", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    ImGui::Text("Fenêtre de l'interface pour la SCENE.");

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

    ImGui::Text("Fenêtre de l'interface pour les OBJECTS.");

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

    ImGui::Text("Fenêtre de l'interface pour les LUMIERES.");

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

    ImGui::End();

}

template<typename VecType>
void ImGuiInterface<VecType>::_drawFrame(float width, float height){
    if (!m_scene_visible){ return; }
    if (m_objects_visible){
        m_renderScene->drawObjects(width, height);
    }
    if (m_lights_visible){
        m_renderScene->drawLights(width, height);
    }
}