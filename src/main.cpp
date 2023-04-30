#include <iostream>

#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"
#include <thread>

typedef struct {
    int id;
    bool isPressed;
} ButtonState;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height); //specify area to render to
    std::cout << "Viewport changed to : [" << width << "][" << height << "]" << std::endl;
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    double lastFrameTime, currentFrameTime = glfwGetTime();
    double deltaTime, fps;
    std::string title = "";

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