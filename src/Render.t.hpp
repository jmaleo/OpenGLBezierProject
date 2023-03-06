#pragma once

#include "_Render.hpp"

/**
 * Setup FBO for  for openGL.
 */
template <typename VecType>
void Render<VecType>::setUp_FBO(float src_width, float src_height)
{

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
template <typename VecType>
void Render<VecType>::setUp_Object(Object<VecType> *obj)
{
    unsigned int *VAO = obj->get_VAO();
    unsigned int *EBO = obj->get_EBO();
    unsigned int *VBOvertices = obj->get_VBOvertices();
    unsigned int *VBOnormales = obj->get_VBOnormales();

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // vertex normals
    glBindBuffer(GL_ARRAY_BUFFER, *VBOnormales);
    glBufferData(GL_ARRAY_BUFFER, normales.size() * sizeof(glm::vec3), &normales[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
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
template <typename VecType>
void Render<VecType>::setUp_Light(Light<VecType> *light)
{
    unsigned int *VAO = light->get_VAO();
    unsigned int *VBOposition = light->get_VBOposition();

    glm::vec3 position = light->getPosition();

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBOposition);

    glBindVertexArray(*VAO);

    // VertexPosition
    glBindBuffer(GL_ARRAY_BUFFER, *VBOposition);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &position, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

template <typename VecType>
void Render<VecType>::bind_HDR()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fboHDR);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

template <typename VecType>
void Render<VecType>::unbind_HDR()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

template <typename VecType>
void Render<VecType>::draw_HDR(ShaderProgram *m_shaderHDR, float width, float height, int hdr, float exposure)
{
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
template <typename VecType>
void Render<VecType>::draw_Object(Object<VecType> *obj, std::vector<Light<VecType> *> lights, ShaderProgram *shader, float width, float height)
{

    unsigned int *VAO = obj->get_VAO();
    std::vector<unsigned int> indices = obj->getIndices();
    Material *mat = obj->getMaterial();

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

    for (int i = 0; i < lights.size(); i++)
    {
        std::string lightPos = "lightPos[" + to_string(i) + "]";
        std::string lightColor = "lightColor[" + to_string(i) + "]";
        shader->setVec3(lightPos, lights.at(i)->getPosition());
        shader->setVec3(lightColor, lights.at(i)->getColor());
    }

    if (obj->isContainer())
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    // draw mesh
    glPointSize(10);
    glBindVertexArray(*VAO);

    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    if (obj->isContainer())
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

/**
 * @brief Draw obj into openGL
 */
template <typename VecType>
void Render<VecType>::draw_Object_Selected(Object<VecType> *obj, std::vector<Light<VecType> *> lights, ShaderProgram *shader, float width, float height)
{

    unsigned int *VAO = obj->get_VAO();
    std::vector<unsigned int> indices = obj->getIndices();
    Material *mat = obj->getMaterial();
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
    shader->setVec3("objectColor", (0.5f + sin(2 * time_now) * 0.5f) * (mat->color));

    shader->setFloat("metallic", mat->metallic);

    shader->setFloat("roughness", mat->roughness);

    shader->setFloat("ao", mat->ao);

    for (int i = 0; i < lights.size(); i++)
    {
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
template <typename VecType>
void Render<VecType>::draw_Light(Light<VecType> *light, ShaderProgram *shader, float width, float height)
{
    unsigned int *VAO = light->get_VAO();
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
template <typename VecType>
void Render<VecType>::draw_Light_Selected(Light<VecType> *light, ShaderProgram *shader, float width, float height)
{
    unsigned int *VAO = light->get_VAO();
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
    shader->setVec3("color", (0.5f + sin(2 * time_now) * 0.5f) * color);

    // draw mesh
    glLineWidth(1);
    glPointSize(10);
    glBindVertexArray(*VAO);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
}

template <typename VecType>
void Render<VecType>::setUp_quad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,
            1.0f,
            0.0f,
            0.0f,
            1.0f,
            -1.0f,
            -1.0f,
            0.0f,
            0.0f,
            0.0f,
            1.0f,
            1.0f,
            0.0f,
            1.0f,
            1.0f,
            1.0f,
            -1.0f,
            0.0f,
            1.0f,
            0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

template <typename VecType>
void Render<VecType>::draw_Particles(Object<VecType> *obj, ShaderProgram *shader, float width, float height)
{

    ParticlesContainer *container = obj->getContainer();

    unsigned int *particleVAO = container->get_particleVAO();
    unsigned int *particleVBO = container->get_particleVBO();
    std::vector<glm::vec3> vertices = container->get_positions();
    // std::cout << "Size of vertices : " << vertices.size() << std::endl;

    if (container->is_setUp() == false)
    {
        glGenVertexArrays(1, particleVAO);
        glGenBuffers(1, particleVBO);
        container->set_setUp(true);
        glBindVertexArray(*particleVAO);
        // vertex positions
        glBindBuffer(GL_ARRAY_BUFFER, *particleVBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
    }

    glBindVertexArray(*particleVAO);
    // vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, *particleVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
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

    glm::vec3 color = container->get_color();
    shader->setVec3("color", color);

    // draw mesh
    // glLineWidth(10);
    glPointSize(container->get_size() * 10);
    glBindVertexArray(*particleVAO);
    glDrawArrays(GL_POINTS, 0, vertices.size());
    glBindVertexArray(0);

    return;
}

template <typename VecType>
void Render<VecType>::setUp_BLOOM(float src_width, float src_height)
{
    glGenFramebuffers(1, &fboHDR);
    glBindFramebuffer(GL_FRAMEBUFFER, fboHDR);
    // create 2 floating point color buffers (1 for normal rendering, other for brightness treshold values)
    glGenTextures(2, colorBuffers);

    for (unsigned int i = 0; i < 2; i++)
    {
        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, (unsigned int)src_width, (unsigned int)src_height, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // attach texture to framebuffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
    }
    // create and attach depth buffer (renderbuffer)
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, (unsigned int)src_width, (unsigned int)src_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering

    glDrawBuffers(2, attachments);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // ping-pong-framebuffer for blurring
    glGenFramebuffers(2, pingpongFBO);
    glGenTextures(2, pingpongBuffers);
    for (unsigned int i = 0; i < 2; i++)
    {   
        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
        glBindTexture(GL_TEXTURE_2D, pingpongBuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, (unsigned int)src_width, (unsigned int)src_height, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongBuffers[i], 0);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer not complete!" << std::endl;
    }
}

// Function blur
template <typename VecType>
void Render<VecType>::blur(ShaderProgram *shader, unsigned int width, unsigned int height, int amount)
{
    m_horizontal = true;

    bool first_iteration = true;

    shader->use();

    for (int i = 0; i < amount; i++)
    {   
        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[m_horizontal]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingpongBuffers[!m_horizontal]); // bind texture of other framebuffer (or scene if first iteration)
        
        shader->setInt("horizontal", m_horizontal);

        setUp_quad();

        m_horizontal = !m_horizontal;
        if (first_iteration)
            first_iteration = false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

template <typename VecType>
void Render<VecType>::draw_BLOOM(ShaderProgram *shader, float width, float height, int hdr, float exposure, int bloom, bool onlyBright)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, pingpongBuffers[!m_horizontal]);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, pingpongBuffers[!m_horizontal]);

    shader->setInt("hdr", hdr);
    shader->setInt("bloom", bloom);
    shader->setFloat("exposure", exposure);
    shader->setInt("OnlyBright", onlyBright);

    setUp_quad();
}