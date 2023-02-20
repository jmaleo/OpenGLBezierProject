#pragma once

#include "_Render.hpp"


/**
 * Setup FBO for  for openGL.
*/
template<typename VecType>
void Render<VecType>::setUp_FBO (float src_width, float src_height){

    glGenFramebuffers(1, &fboHDR);
    // create floating point color buffer
    glGenTextures(1, &colorBuffer);
    glBindTexture(GL_TEXTURE_2D, colorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, (const unsigned int)src_width, (const unsigned int)src_height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // create depth buffer (renderbuffer)
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, src_width, src_height);
    // attach buffers
    glBindFramebuffer(GL_FRAMEBUFFER, fboHDR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return;
}

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

template<typename VecType>
void Render<VecType>::bind_HDR(){
    glBindFramebuffer(GL_FRAMEBUFFER, fboHDR);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

template<typename VecType>
void Render<VecType>::unbind_HDR(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

template<typename VecType>
void Render<VecType>::draw_HDR(ShaderProgram* m_shaderHDR, float width, float height, int hdr, float exposure){
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shaderHDR->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, colorBuffer);
    m_shaderHDR->setInt("hdr", hdr);
    m_shaderHDR->setFloat("exposure", exposure);
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

/**
 * @brief Draw obj into openGL
*/
template<typename VecType>
void Render<VecType>::draw_Object (MyObject<VecType>* obj, std::vector<Light<VecType>*> lights, ShaderProgram* shader, float width, float height){
    
    unsigned int* VAO = obj->get_VAO();
    std::vector<unsigned int> indices = obj->getIndices();
    Material* mat = obj->getMaterial();
    
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

    shader->setVec3("objectColor", mat->color);

    shader->setFloat("metallic", mat->metallic);

    shader->setFloat("roughness", mat->roughness);
    
    shader->setFloat("ao", mat->ao);

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
    Material* mat = obj->getMaterial();
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
    shader->setVec3("objectColor", (0.5f + sin(2*time_now)*0.5f) * (mat->color));

    shader->setFloat("metallic", mat->metallic);

    shader->setFloat("roughness", mat->roughness);
    
    shader->setFloat("ao", mat->ao);


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

template<typename VecType>
void Render<VecType>::setUp_quad () {
    float quadVertices[] = {
        // positions        // texture Coords
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };
    // setup plane VAO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); 
}


template<typename VecType>
void Render<VecType>::draw_Particles (std::vector<Particle*> particles, ShaderProgram* shader, float width, float height){

    // update_particles(particles, 1);

    std::vector<VecType> vertices;
    for (int i = 0; i < particles.size(); i++){
        vertices.push_back(particles.at(i)->get_position());
    }

    glGenVertexArrays(1, &particleVAO);
    glGenBuffers(1, &particleVBO);

    glBindVertexArray(particleVAO);

    // vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, particleVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

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

    glm::vec3 color = particles.at(0)->get_material()->color;
    shader->setVec3("color", color);

    // draw mesh
    glLineWidth(1);
    glPointSize(particles.at(0)->get_size());
    glBindVertexArray(particleVAO);
    glDrawArrays(GL_POINTS, 0, vertices.size());
    glBindVertexArray(0);

    return;
}