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

#include "Scene.t.hpp"
#include "Object.t.hpp"
#include "Light.t.hpp"
#include "Render.t.hpp"
#include "_ControlGLSL.hpp"

template<typename VecType>
class RenderScene {

    public: 
        RenderScene (Scene<VecType>* scene);

        /**
         * @brief SetUp rendering.
         */
        void setUp (float src_width, float src_height);


        /**
         * @brief Does all the draw process.
         * @param selection : 0 if no object or light is selected, 1 for object and 2 for light and 3 for both.
         */
        void draw (float width, float height, int selection);

        void addLight ();

        Material* getMaterial (int id);

        VecType getPosition(int id, bool obj);

        float* getExposure () { return &m_exposure; }

        glm::vec3 getLightColor(int id);

        void setHDR (bool h) { m_hdr = h; }

        void setBloom (bool b) { m_bloom = b; }

        void setOnlyBright (bool b) { m_onlyBright = b; }

        void setMaterial (int id, Material mat);

        void setLightColor(int id, float* color);

        std::vector <int> getObjectIds ();

        std::vector <int> getLightIds ();

        void setObjectSelected (int id);

        void setLightSelected (int id);

        void setTempLight (Light<VecType>* l ) { m_temp_light = l; }
        void setTempObject (Object<VecType>* o ) { m_temp_object = o; }

        Light<VecType>* getTempLight () { return m_temp_light; }
        Object<VecType>* getTempObject () { return m_temp_object; }

        glm::vec3 getCameraPosition () { return m_myScene->getCamera()->Position; }

        void initShaders();

        void resetGLSL();

        void initGLSL();

        void setStopParticles (bool b) { m_stopParticles = b; }

        void setDeltaTime (float dt) { m_deltaTime = dt; }

        void setParticlesVisible (bool b) { m_particlesVisible = b; }

        // Position : 1 for uniform disposition and 0 for the center.
        void resetParticles (int nbParticles, int position);

        bool isContainer(int id);

        void setObjPosition(int id, VecType pos);

        void setLightPosition(int id, VecType pos);

    private:

        std::string m_vertexShader_name = "vertexShader.glsl";
        std::string m_fragmentShader_name = "fragmentShader.glsl";
        
        std::string m_vertexShaderLight_name = "vertexLight.glsl";
        std::string m_fragmentShaderLight_name = "fragmentLight.glsl";

        std::string m_vertexShaderHDR_name = "vertexHDR.glsl";
        std::string m_fragmentShaderHDR_name = "fragmentHDR.glsl";

        std::string m_vertexShaderBloom_name = "vertexBLOOM.glsl";
        std::string m_fragmentShaderBloom_name = "fragmentBLOOM.glsl";

        std::string m_vertexShaderBlur_name = "vertexBLUR.glsl";
        std::string m_fragmentShaderBlur_name = "fragmentBLUR.glsl";

        std::string m_path_vertexShader = SHADER_DIR + m_vertexShader_name;
        std::string m_path_fragmentShader = SHADER_DIR + m_fragmentShader_name;

        std::string m_path_vertexShaderLight = SHADER_DIR + m_vertexShaderLight_name;
        std::string m_path_fragmentShaderLight = SHADER_DIR + m_fragmentShaderLight_name;

        std::string m_path_vertexShaderHDR = SHADER_DIR + m_vertexShaderHDR_name;
        std::string m_path_fragmentShaderHDR = SHADER_DIR + m_fragmentShaderHDR_name;

        std::string m_path_vertexShaderBloom = SHADER_DIR + m_vertexShaderBloom_name;
        std::string m_path_fragmentShaderBloom = SHADER_DIR + m_fragmentShaderBloom_name;

        std::string m_path_vertexShaderBlur = SHADER_DIR + m_vertexShaderBlur_name;
        std::string m_path_fragmentShaderBlur = SHADER_DIR + m_fragmentShaderBlur_name;

        // Used to debug for instance.
        ShaderProgram* m_shaderObj;

        ShaderProgram* m_shaderLight;

        ShaderProgram* m_shaderHDR;

        ShaderProgram* m_shaderBloom;

        ShaderProgram* m_shaderBlur;


        Render<VecType>* m_render;
        Scene<VecType>* m_myScene;

        Light<VecType>* m_temp_light = nullptr;
        Object<VecType>* m_temp_object = nullptr;

        int m_selected = -1;
        bool m_selected_object = false;
        bool m_selected_light = false;

        bool m_particlesVisible = true;
        bool m_stopParticles = true;
        float m_deltaTime = 0.1f;

        bool m_hdr = true;
        bool m_bloom = true;
        float m_exposure = 2.0f;
        bool m_onlyBright = false;

        void m_setUpObjects ();

        void m_setUpLights ();

        void m_drawObjects (float width, float height);

        void m_drawLights (float width, float height);

        void m_drawObjSelection (int objIds, float width, float height);

        void m_drawLightSelection (int lightIds, float width, float height);

        void m_draw_new(float width, float height, int selection);

};