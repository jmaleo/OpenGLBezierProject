#include "_Interface.hpp"

/**
 * @brief 
 * TODO
 * 
 * @tparam VecType 
 */
template<typename VecType>
void ImGuiInterface<VecType>::draw(){
    _drawInterface();
    _drawScene();
    _drawObject();
    _drawLights();
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

    ImGui::SetNextWindowPos( ImVec2( m_begin_win, m_size_offset ) );
    ImGui::SetNextWindowSize( ImVec2( m_size_width, 0) );
    ImGui::Begin("Test_Interface_OBJECTS", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    ImGui::Text("Fenêtre de l'interface pour les OBJECTS.");

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

    ImGui::SetNextWindowPos( ImVec2( m_begin_win, m_size_offset ) );
    ImGui::SetNextWindowSize( ImVec2( m_size_width, 0) );
    ImGui::Begin("Test_Interface_LIGHTS", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    ImGui::Text("Fenêtre de l'interface pour les LUMIERES.");

    ImGui::End();

}