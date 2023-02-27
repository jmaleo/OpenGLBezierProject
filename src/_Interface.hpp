#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <time.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <filesystem>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "structures.hpp"
#include "Scene.t.hpp"
#include "Render_scene.t.hpp"
#include "_ControlGLSL.hpp"


// J'ai besoin pour cette classe de pouvoir TOUT panipuler, puisque je veux que l'utilisateur intéragisse avec TOUT.
template <typename VecType>
class ImGuiInterface {
    public:

        ImGuiInterface( RenderScene<VecType>* renderScene ){
            m_renderScene = renderScene;
        };
        
        void draw(float width, float height);

        void quit ();
    
    private:

        // Function that displays the entire thing.
        void _drawInterface();

        // Function that displays the pannel for the current scene.
        void _drawScene();

        // Function that displays the pannel for Objects.
        void _drawObject();

        // Function that displays the pannel for lights.
        void _drawLights();

        // Function that draw the openGL frame, following the interface.
        void _drawFrame(float width, float heigth);

        // Function that draw the information of a selected light or object
        void _drawSelectInformation();

        // Draw new object or light before appying.
        void _drawNewInformation(float width, float height);

        
        // Indicates the size (width) of a widget. 
        int m_size_width = 200;
        int m_size_offset = 10;

        // Variable that indicates where is the next widget pos.
        int m_begin_win = m_size_offset;

        // Variables indicating the visibility of windows.
        bool m_scene_visible = true;
        bool m_lights_visible = true;
        // bool m_objects_visible = true;
        bool m_objects_visible = false;
        bool m_onlyBright = false;

        bool m_selected_light = false;
        bool m_selected_object = false;
        int m_selected = -1;

        bool m_hdr = true;
        bool m_bloom = true;

        // Variables
        RenderScene<VecType>* m_renderScene;

        // Variables for the object's material
        Material* m_selected_mat;

        bool m_newThing = false;
        VecType first_position;
};