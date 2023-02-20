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
#include "Light.t.hpp"
#include "Particle.t.hpp"

template <typename VecType>
class Scene {

    public: 
        Scene (Camera* cam) { m_cam = cam; }

        virtual ~Scene();

        /**
         * @brief 
         * TODO
         * 
         * @param obj 
         * @param id 
         */
        void addObject (MyObject<VecType>* obj);

        /**
         * @brief 
         * TODO
         * 
         * @param light 
         * @param id 
         */
        void addLight (Light<VecType>* light);

        void addParticles (std::vector<Particle*> particles) { m_particles = particles; };

        /**
         * @brief 
         * TODO
         * 
         * @param id 
         */
        void deleteObject (int id);

        /**
         * @brief 
         * TODO
         * 
         * @param id 
         */
        void deleteLight (int id);

        /**
         * @brief 
         * TODO
         * 
         */
        void cleanScene ();

        /**
         * 
         */
        int getNumberObjects() { return m_numObj; }

        /**
         * 
         */
        std::vector < MyObject <VecType>* > getListObjects() { return m_listObjects; }

        /**
         * 
         */
        std::vector < Light<VecType>* > getListLights () { return m_listLights; }

        std::vector < Particle* > getParticles () { return m_particles; }

        /**
         * 
         */
        Camera* getCamera () { return m_cam; }

    private:
        Camera* m_cam;

        int m_numObj = 0;

        int m_lastId_object = 0;
        int m_lastId_light = 0;

        std::vector < MyObject<VecType>* > m_listObjects;
        std::vector < Light<VecType>* > m_listLights;
        std::vector < Particle* > m_particles;

};