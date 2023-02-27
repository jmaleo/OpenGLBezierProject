#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include "ShaderProgram.h"
#include "Camera.h"

#include "Object.t.hpp"
#include "Light.t.hpp"
#include "ParticlesContainer.t.hpp"
#include "structures.hpp"

template <typename VecType>
class Render {

    public: 

        Render (Camera* cam) { m_camera = cam; };

        // virtual ~Render();

        void setUp_FBO (float src_width, float src_height);

        void setUp_quad ();

        void setUp_Object (Object<VecType>* obj);

        void setUp_Light (Light<VecType>* light);

        void bind_HDR ();
        void unbind_HDR ();

        void setUp_BLOOM (float src_width, float src_height);
        void blur (ShaderProgram* shader, unsigned int width, unsigned int height, int amount);

        void draw_HDR(ShaderProgram* m_shaderHDR, float width, float height, int hdr, float exposure);
        void draw_BLOOM (ShaderProgram* shader, float width, float height, int hdr, float exposure, int bloom, bool onlyBright);

        void draw_Object (Object<VecType>* obj, std::vector<Light<VecType>*> lights, ShaderProgram* shader, float width, float height);
        void draw_Object_Selected (Object<VecType>* obj, std::vector<Light<VecType>*> lights, ShaderProgram* shader, float width, float height);

        void draw_Light (Light<VecType>* light, ShaderProgram* shader, float width, float height);
        void draw_Light_Selected (Light<VecType>* light, ShaderProgram* shader, float width, float height);

        void draw_Particles (Object<VecType>*obj, ShaderProgram* shader, float width, float height);

    private:
        Camera* m_camera;

        unsigned int quadVAO = 0;
        unsigned int quadVBO;

        // HDR
        unsigned int fboHDR;
        unsigned int colorBuffer;
        unsigned int rboDepth;

        // Bloom
        unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
        unsigned int colorBuffers[2];
        unsigned int pingpongFBO[2];
        unsigned int pingpongBuffers[2];

        bool m_horizontal = true;

        // void m_drawQuad();
};