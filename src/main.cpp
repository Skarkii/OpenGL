#include <iostream>

#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"
#include <thread>
#include "vbo.h"
#include "vao.h"
#include "shader.h"
#include "shaderProgram.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height); //specify area to render to
    std::cout << "Viewport changed to : [" << width << "][" << height << "]" << std::endl;
}

#include <fstream>
const char* getDataFromFile(const char* filename)
{
    std::ifstream file(filename);

    if(!file.is_open()){
        std::cout << "Couldn't open file " << filename << std::endl;
        return nullptr;
    }

    file.seekg(0, std::ios::end);

    std::string buffer;
    buffer.resize(file.tellg());

    file.seekg(0, std::ios::beg);

    file.read(&buffer[0], buffer.size());

    file.close();
    return buffer.c_str();
}


void renderLoop(GLFWwindow* window, int width, int height)
{
    //Init GLAD
    glfwMakeContextCurrent(window); //Required to init GLAD

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwSetWindowShouldClose(window, true);
        return;
    }
    glViewport(0,0,width,height); // Set default viewport
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    double lastFrameTime, currentFrameTime = glfwGetTime();
    double deltaTime, fps;
    std::string title = "";
    
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };  

    Shader* vertexShader = new Shader(getDataFromFile("shaders/default.vert"), GL_VERTEX_SHADER);
    Shader* fragmentShader = new Shader(getDataFromFile("shaders/default.frag"), GL_FRAGMENT_SHADER);

    ShaderProgram program = ShaderProgram();

    program.AttachShader(vertexShader);

    program.AttachShader(fragmentShader);

    program.Link();

    VBO vbo = VBO();
    VAO vao = VAO();

    vao.Bind();

    vbo.Bind();
    
    vbo.SetBufferData(vertices, sizeof(vertices));

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

    vao.LinkVBO(vbo);

    vbo.Unbind();
    vao.Unbind();



    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(window)) // Render Loop
    {
        //FPS CALCULATION
        currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
        fps = 1.0 / deltaTime;
        title = "Game - " + std::to_string((int)fps);
        glfwSetWindowTitle(window, title.c_str());
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.SetActive();

        vao.Bind();

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }
}



void toggleFullscreen(GLFWwindow* window)
{
    if(glfwGetWindowMonitor(window) == NULL)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else
    {
        glfwSetWindowMonitor(window, NULL, 20, 20, 1280, 720, GLFW_DONT_CARE);
    }
}


typedef struct {
    int id;
    bool isPressed;
} ButtonState;


void processInput(GLFWwindow* window, ButtonState* onePerClickButtons)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {    
        glfwSetWindowShouldClose(window, true);
        return;
    }

    if(glfwGetKey(window, onePerClickButtons[0].id) == GLFW_PRESS && !onePerClickButtons[0].isPressed)
    {
        onePerClickButtons[0].isPressed = true;
        toggleFullscreen(window);
    }
    else if(glfwGetKey(window, GLFW_KEY_F11)  == GLFW_RELEASE && onePerClickButtons[0].isPressed)
    {
        onePerClickButtons[0].isPressed = false;
    }


    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        
    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        
    }

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
    }

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
    }
}

int main()
{
    //Init glfw
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int width = 1280;
    int height = 720;
    std::string title = "Title"; 



    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if(window == NULL) //Create window
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        system("pause");
        glfwTerminate();
        return -1;
    }

    std::thread renderThread(renderLoop, window, width, height); //Create render loop


    ButtonState onePerClickButtons[2]
    {
        { GLFW_KEY_F11, false },
        { GLFW_KEY_F12, false }
    };
    
    

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window, onePerClickButtons); 
        glfwPollEvents();
    }

    ///Termination
    renderThread.join();
    glfwTerminate();
    return 0;
}