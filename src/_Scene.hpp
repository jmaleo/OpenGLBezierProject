#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include "Object.t.hpp"

template <typename VecType>
class Scene {

    public: 
        Scene ();

        virtual ~Scene();

        /**
         * @brief 
         * TODO
         * 
         * @param obj 
         * @param name 
         */
        void addObject (MyObject<VecType> obj, std::string name);

        /**
         * @brief 
         * TODO
         * 
         * @param name 
         */
        void deleteObject (std::string name);

        /**
         * @brief 
         * TODO
         * 
         */
        void cleanScene ();

    private:
};