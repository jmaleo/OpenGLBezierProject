#pragma once



#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CMakeConfig.h"

#include <iostream>
#include <fstream>
#include <string>

#include "ShaderProgram.h"
#include "Camera.h"

#include "Object.t.hpp"
#include "Scene.t.hpp"
#include "Render.t.hpp"

template<typename VecType>
class RenderScene {

    public: 
        RenderScene (Scene<VecType>* scene);

        void setUpObjects ();

        void setUpLights ();

        void drawObjects (float width, float height);

        void drawLights (float width, float height);


    private:
        std::string m_vertexShader_name = "vertexShader.glsl";
        std::string m_fragmentShader_name = "fragmentControl.glsl";
        // need to .c_str() before sending to a shaderProgram
        std::string m_path_vertexShader = SHADER_DIR + m_vertexShader_name;
        std::string m_path_fragmentShader = SHADER_DIR + m_fragmentShader_name;

        std::string m_vertexShaderLight_name = "vertexLight.glsl";
        std::string m_fragmentShaderLight_name = "fragmentLight.glsl";
        std::string m_path_vertexShaderLight = SHADER_DIR + m_vertexShaderLight_name;
        std::string m_path_fragmentShaderLight = SHADER_DIR + m_fragmentShaderLight_name;


        // Used to debug for instance.
        ShaderProgram* m_shaderControl = new ShaderProgram(m_path_vertexShader.c_str(), m_path_fragmentShader.c_str());
        ShaderProgram* m_shaderTest = new ShaderProgram(m_path_vertexShader.c_str(), (SHADER_DIR + std::string("fragmentShader.glsl")).c_str());
        ShaderProgram* m_shaderLight = new ShaderProgram(m_path_vertexShaderLight.c_str(), m_path_fragmentShaderLight.c_str());

        Render<VecType>* m_render;
        Scene<VecType>* m_myScene;

};