#include <glad/glad.h>
//#include <stb_image.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <filesystem>
#include <time.h>

#include "ShaderProgram.h"
#include "Camera.h"
#include "BezierSurface.h"
#include "BezierSurfaceMesh.h"
#include "ControlCurveMesh.h"
#include "ControlSurfaceMesh.h"
#include "lightMesh.h"
#include "NormalMesh.h"
#include "Objects.h"
#include "Lights.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <time.h>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "CMakeConfig.h"


#include "Interface.t.hpp"
#include "Scene.t.hpp"
#include "Object.t.hpp"
#include "Render.t.hpp"
#include "utils.t.hpp"
#include "Render_scene.t.hpp"



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

ControlCurveMesh* controlCurveMesh;

BezierSurface* bSurface;
BezierSurfaceMesh* bSurfaceMesh;
ControlSurfaceMesh* controlSurfaceMesh;
NormalMesh* normalMeshLines; 
NormalMesh* normalMeshColored;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool pressedMouse = false;


RenderScene<glm::vec3>* myRender = nullptr;
ImGuiInterface<glm::vec3>* myInterface = nullptr;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int lines = GL_LINE;
bool lineChange = true;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Bezier Curve and Surface Project", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    srand(time(NULL));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

	// LIGHTS coming from lights.h
    vector<glm::vec3> lights = lightsVector3();
	
	// Bezier SURFACE
	glm::vec3 surfaceColor = glm::vec3(0.5f, 0.7f, 0.7f);
    vector<vector<glm::vec3>> control = randomPointsSurface(10.0f, 4.0f);
    bSurface = new BezierSurface(control, surfaceColor);


	// SURFACE MESH
    bSurfaceMesh = new BezierSurfaceMesh(bSurface->getCurve(), bSurface->getSurfaceColor(), lights, &camera);
    controlSurfaceMesh = new ControlSurfaceMesh(control, &camera);
    normalMeshLines = new NormalMesh(bSurfaceMesh->getVertices(), bSurfaceMesh->getNormales(), &camera);
    normalMeshColored = new NormalMesh(bSurfaceMesh->getVertices(), bSurfaceMesh->getIndices(), bSurfaceMesh->getNormales(), lights, &camera);

    //LIGHTS
    LightMesh* lightMesh = new LightMesh(bSurfaceMesh->getLightsPos(), bSurfaceMesh->getLightsColor(), &camera);

    //LIGHT
    lightMesh->setupMesh();
	
	//SURFACE
    bSurfaceMesh->setupMesh();
    controlSurfaceMesh->setupMesh();
    normalMeshLines->setupMesh();
	normalMeshColored->setupMesh();

    // Shaders instanciation
    ShaderProgram* shaderLights = new ShaderProgram((SHADER_DIR+std::string("vertexLight.glsl")).c_str(), (SHADER_DIR+std::string("fragmentLight.glsl")).c_str());

    ShaderProgram* shaderSurface = new ShaderProgram((SHADER_DIR+std::string("vertexShader.glsl")).c_str(), (SHADER_DIR+std::string("fragmentShader.glsl")).c_str());
    ShaderProgram* shaderControl = new ShaderProgram((SHADER_DIR+std::string("vertexShader.glsl")).c_str(), (SHADER_DIR+std::string("fragmentControl.glsl")).c_str());
	ShaderProgram* shaderNormalLines = new  ShaderProgram((SHADER_DIR+std::string("vertexShader.glsl")).c_str(), (SHADER_DIR+std::string("fragmentCurve.glsl")).c_str());
    ShaderProgram* shaderNormalColored = new  ShaderProgram((SHADER_DIR+std::string("vertexShader.glsl")).c_str(), (SHADER_DIR+std::string("fragmentNormal.glsl")).c_str());

    bool show_another_window = true;


    /**
     *  
     * 
     * 
     *   DEBUG DEBUG DEBUG DEBUG
     * 
     * 
     */

    /*
        Dans l'idée : - On setup une caméra.
                      - On setup une scene. -> Objets / lights
                      - On crée une RenderScene, qui permettra à l'UI d'intéragir avec la scene.
                      - On setup l'UI.
                      - C'est gagné.
    */

    // Scene<glm::vec3> myScene;
    Scene<glm::vec3>* myScene = generateCubeScene(&camera, glm::vec3(-50.0f,50.0f,-50.0f), 100.0f, 2, 5);
    
    myRender = new RenderScene<glm::vec3>(myScene);
    myInterface = new ImGuiInterface<glm::vec3>(myRender);

    myRender->setUpObjects();
    myRender->setUpLights();
    

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        processInput(window);

        //rendering commands here
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

		//LIGHT
        // lightMesh->draw(shaderLights, float(SCR_WIDTH), float(SCR_HEIGHT));

		// Just press L to show triangles or facettes
        glPolygonMode(GL_FRONT_AND_BACK, lines);

        myInterface->draw((float)SCR_WIDTH, (float)SCR_HEIGHT);
        // myRender.draw_Object(&firstCube, shaderControl, (float)SCR_WIDTH, (float)SCR_HEIGHT);

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

    }
     
    //SURFACE
    bSurface->deleteSurface();
	delete bSurface;
	delete bSurfaceMesh;
    delete controlSurfaceMesh;
    delete shaderControl;
    delete shaderNormalLines;
    delete shaderNormalColored;
    delete myScene;
    delete myInterface;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && lineChange) {
        lines = (lines == GL_FILL) ? GL_LINE : GL_FILL;
        lineChange = false;
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE)
        lineChange = true;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        pressedMouse = true;
        firstMouse = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        pressedMouse = false;
    }
    
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    if (pressedMouse) {
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is calle
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}