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


class ImGuiInterface {
    public:

        ImGuiInterface(){
            std::cout << "You choose the classic interface." << std::endl;
        };
        
        void draw();
    
    private:

        void _drawCurve();
};