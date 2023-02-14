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
// #include "Lights.t.hpp"
#include "Lights.h"

template <typename VecType>
class Render {

    public: 

        Render (Camera* cam) { m_camera = cam; };

        // virtual ~Render();

        void setUp_Object (MyObject<VecType>* obj);

        void setUp_Light (Light<VecType>* light);

        void draw_Object (MyObject<VecType>* obj, std::vector<Light<VecType>*> lights, ShaderProgram* shader, float width, float height);

        void draw_Light (Light<VecType>* light, ShaderProgram* shader, float width, float height);


    private:

        Camera* m_camera;
};