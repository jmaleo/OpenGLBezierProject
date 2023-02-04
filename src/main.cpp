#include <glad/glad.h>
//#include <stb_image.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <filesystem>

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

void showPrompt();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void updateCurve();
void controlChange();

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

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int lines = GL_LINE;
bool lineChange = true;

bool showParam = false;
bool paramChange = true;

int showNormal = 0;
bool normalChange = true;

bool showBezier = true;
bool bezierChange = true;

int showCurve = 0;
bool curveChange = true;

bool curveParamChange = true;
float offSetLine = 0.5f;
int nbLine = 5;

bool randomChange = true;



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
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                                                                                                                     //
	//         HOW TO USE THIS PROGRAM                                                                                                                     //
	//  By pressing C on your keyboard, you can change between a bezier curve with X lines, a bezier curve with lines of Y length and a bezier surface.    //
	//  By pressing P you can see the control polynom.                                                                                                     //
	//  During the surface scene, you can press on N to see normal as lines or normal as color (interpoled).                                               //
    //  You can also, at any time, press on B to see or not Curve or Surface.                                                                              //
    //  You can PRESS R to generate random control points                                  	  						                     			       //
    //                                          																                                           //
    //  ALSO, for curves you may play with right or left arrow to change parameters as nb of Lines or offSet                                               //
    //                                                                                                                                                     //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    showPrompt();


	// LIGHTS coming from lights.h
    vector<glm::vec3> lights = lightsVector3();

	
   	//Be carefull, controlPoints coming from Objects.h
	
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

		
        // CURVE
        if (showCurve == 0 || showCurve == 1) {
            //Polynome de control
			if (showParam)
                controlCurveMesh->draw(shaderControl, float(SCR_WIDTH), float(SCR_HEIGHT));
        }
        else {
            //Polynome de control
            if (showParam)
                controlSurfaceMesh->draw(shaderControl, float(SCR_WIDTH), float(SCR_HEIGHT));
            //NORMALS
            if (showNormal > 0) {
                //SHOW NORMAL AS LINES
                if (showNormal == 1)
                    normalMeshLines->draw(shaderNormalLines, float(SCR_WIDTH), float(SCR_HEIGHT));
                // SHOW NORMAL AS COLOR
                else
                    normalMeshColored->draw(shaderNormalColored, float(SCR_WIDTH), float(SCR_HEIGHT));
            }
            // SHOW BEZIER SURFACE
            if (showBezier)
                bSurfaceMesh->draw(shaderSurface, (float)SCR_WIDTH, (float)SCR_HEIGHT);
        }
		//LIGHT
        lightMesh->draw(shaderLights, float(SCR_WIDTH), float(SCR_HEIGHT));

		// Just press P to show triangles or facettes
        glPolygonMode(GL_FRONT_AND_BACK, lines);

        ImGui::SetNextWindowPos(ImVec2(0,0));
        ImGui::Begin("Example Window", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        // ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
        
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
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && paramChange) {
        showParam = (showParam) ? false : true;
        paramChange = false;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
        paramChange = true;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && normalChange) {
        showNormal = (showNormal + 1) % 3;
        normalChange = false;
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE)
        normalChange = true;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && bezierChange) {
        showBezier = (showBezier) ? false : true;
        bezierChange = false;
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE)
        bezierChange = true;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && curveChange) {
        showCurve = (showCurve + 1) % 3;
        curveChange = false;
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)
        curveChange = true;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && curveParamChange) {
        if (showCurve == 0)
            nbLine += 1;
        if (showCurve == 1)
            offSetLine = (offSetLine >= 10.0f)?1.0f:offSetLine + 0.05f;
        curveParamChange = false;
        updateCurve();
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && curveParamChange) {
        curveParamChange = false;
        if (showCurve == 0)
            nbLine = (nbLine == 1)?1:nbLine-1;
        if (showCurve == 1)
            offSetLine = (offSetLine <= 0.05f) ? 0.05f : offSetLine - 0.05f;
        updateCurve();
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE)
        curveParamChange = true;
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && randomChange) {
        randomChange = false;
        controlChange();
    }
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE)
		randomChange = true;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        pressedMouse = true;
        firstMouse = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        pressedMouse = false;
    
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

void updateCurve() {
    if (showCurve == 2)
        return;
    if (showCurve == 0) {
        cout << "nbLine = " << nbLine <<  endl;
    }
    else {
        cout << "offSetLine = " << offSetLine << endl;
    }
}

void controlChange() {
    if (showCurve == 0 || showCurve == 1) {
        vector <glm::vec3> controlPoints = randomPointsCurve();
        controlCurveMesh->setControlPoints(controlPoints);		
    }
    else {
		vector<vector<glm::vec3>> controlPoints = randomPointsSurface(10, 4);
		bSurface->setControlPoints(controlPoints);
        controlSurfaceMesh->setVertices(controlPoints);
		bSurfaceMesh->setVertices(bSurface->getCurve());
        normalMeshLines->setVerticesAndNormals(bSurfaceMesh->getVertices(), bSurfaceMesh->getNormales());
        normalMeshColored->setVerticesAndNormals(bSurfaceMesh->getVertices(), bSurfaceMesh->getIndices(), bSurfaceMesh->getNormales());
		
    }
}

void showPrompt() {
    cout << "/////////////////////////////////////////////////////////////////// " <<endl;
    cout << "\t\t HOW TO USE THIS PROGRAM "<< endl;
    cout << "By pressing C on your keyboard, you can change between a bezier curve with X lines, a bezier curve with lines of Y length and a bezier surface." << endl;
    cout << "By pressing P you can see the control polynom." << endl;
	cout << "During the surface scene, you can press on N to see normal as lines or normal as color (interpoled)." << endl;
	cout << "You can also, at any time, press on B to see or not Curve or Surface." << endl;
	cout << "You can PRESS R to generate random control points" << endl;
	cout << "ALSO, for curves you may play with right or left arrow to change parameters as nb of Lines or offSet" << endl;
	cout << "/////////////////////////////////////////////////////////////////// " <<endl;

}