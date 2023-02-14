#pragma once

#include "_Render.hpp"


/**
 * Setup Object for openGL.
*/
template<typename VecType>
void Render<VecType>::setUp_Object (MyObject<VecType>* obj){
    unsigned int* VAO = obj->get_VAO();
    unsigned int* EBO = obj->get_EBO();
    unsigned int* VBOvertices = obj->get_VBOvertices();
    unsigned int* VBOnormales = obj->get_VBOnormales();

    std::vector<VecType> vertices = obj->getVertices();
    std::vector<unsigned int> indices = obj->getIndices();
    std::vector<VecType> normales = obj->getNormales();


    glGenVertexArrays(1, VAO);
    glGenBuffers(1, EBO);
    glGenBuffers(1, VBOvertices);
    glGenBuffers(1, VBOnormales);

    glBindVertexArray(*VAO);

    // vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, *VBOvertices);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //vertex normals
    glBindBuffer(GL_ARRAY_BUFFER, *VBOnormales);
    glBufferData(GL_ARRAY_BUFFER, normales.size() * sizeof(glm::vec3), &normales[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int),
        &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
    return;
}

/**
 * @brief Setup obj for openGL
*/
template<typename VecType>
void Render<VecType>::setUp_Light (Light<VecType>* light){
    unsigned int* VAO = light->get_VAO();
    unsigned int* VBOposition = light->get_VBOposition();

    glm::vec3 position = light->getPosition();
    

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBOposition);

    glBindVertexArray(*VAO);
    
    //VertexPosition
    glBindBuffer(GL_ARRAY_BUFFER, *VBOposition);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &position, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

/**
 * @brief Draw obj into openGL
*/
template<typename VecType>
void Render<VecType>::draw_Object (MyObject<VecType>* obj, std::vector<Light<VecType>*> lights, ShaderProgram* shader, float width, float height){
    
    unsigned int* VAO = obj->get_VAO();
    std::vector<unsigned int> indices = obj->getIndices();
    
    shader->use();

    // pass projection matrix to shader (note that in this case it could change every frame)
    glm::mat4 projection = glm::perspective(glm::radians(m_camera->Zoom), width / height, 0.1f, 100.0f);
    shader->setMat4("projection", projection);

    shader->setVec3("cameraPosition", m_camera->Position);

    // camera/view transformation
    glm::mat4 view = m_camera->GetViewMatrix();
    shader->setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    shader->setMat4("model", model);

    shader->setVec3("objectColor", obj->getColor());

    for (int i = 0; i < lights.size(); i++){
        std::string lightPos = "lightPos[" + to_string(i) + "]";
        std::string lightColor = "lightColor[" + to_string(i) + "]";
        shader->setVec3(lightPos, lights.at(i)->getPosition());
        shader->setVec3(lightColor, lights.at(i)->getColor());
    }

    // draw mesh
    glPointSize(10);
    glBindVertexArray(*VAO);

    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

/**
 * @brief Draw obj into openGL
*/
template<typename VecType>
void Render<VecType>::draw_Object_Selected (MyObject<VecType>* obj, std::vector<Light<VecType>*> lights, ShaderProgram* shader, float width, float height){
    
    unsigned int* VAO = obj->get_VAO();
    std::vector<unsigned int> indices = obj->getIndices();
    
    shader->use();

    // pass projection matrix to shader (note that in this case it could change every frame)
    glm::mat4 projection = glm::perspective(glm::radians(m_camera->Zoom), width / height, 0.1f, 100.0f);
    shader->setMat4("projection", projection);

    shader->setVec3("cameraPosition", m_camera->Position);

    // camera/view transformation
    glm::mat4 view = m_camera->GetViewMatrix();
    shader->setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    shader->setMat4("model", model);

    float time_now = glfwGetTime();
    shader->setVec3("objectColor", (0.5f + sin(2*time_now)*0.5f) * (obj->getColor()));

    for (int i = 0; i < lights.size(); i++){
        std::string lightPos = "lightPos[" + to_string(i) + "]";
        std::string lightColor = "lightColor[" + to_string(i) + "]";
        shader->setVec3(lightPos, lights.at(i)->getPosition());
        shader->setVec3(lightColor, lights.at(i)->getColor());
    }

    // draw mesh
    glPointSize(10);
    glBindVertexArray(*VAO);

    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

/**
 * @brief Draw light into openGL
*/
template<typename VecType>
void Render<VecType>::draw_Light (Light<VecType>* light, ShaderProgram* shader, float width, float height){
    unsigned int* VAO = light->get_VAO();
    shader->use();

    // pass projection matrix to shader (note that in this case it could change every frame)
    glm::mat4 projection = glm::perspective(glm::radians(m_camera->Zoom), width / height, 0.1f, 100.0f);
    shader->setMat4("projection", projection);

    shader->setVec3("cameraPosition", m_camera->Position);

    // camera/view transformation
    glm::mat4 view = m_camera->GetViewMatrix();
    shader->setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    shader->setMat4("model", model);

    glm::vec3 color = light->getColor();
    shader->setVec3("color", color);


    // draw mesh
    glLineWidth(1);
    glPointSize(10);
    glBindVertexArray(*VAO);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
}

/**
 * @brief Draw light into openGL
*/
template<typename VecType>
void Render<VecType>::draw_Light_Selected (Light<VecType>* light, ShaderProgram* shader, float width, float height){
    unsigned int* VAO = light->get_VAO();
    shader->use();

    // pass projection matrix to shader (note that in this case it could change every frame)
    glm::mat4 projection = glm::perspective(glm::radians(m_camera->Zoom), width / height, 0.1f, 100.0f);
    shader->setMat4("projection", projection);

    shader->setVec3("cameraPosition", m_camera->Position);

    // camera/view transformation
    glm::mat4 view = m_camera->GetViewMatrix();
    shader->setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    shader->setMat4("model", model);

    float time_now = glfwGetTime();

    glm::vec3 color = light->getColor();
    shader->setVec3("color", (0.5f + sin(2*time_now)*0.5f) * color);


    // draw mesh
    glLineWidth(1);
    glPointSize(10);
    glBindVertexArray(*VAO);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
}