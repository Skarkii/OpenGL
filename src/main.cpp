//OpenGL
#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"

//C/C++ 
#include <thread>
#include <iostream>
#include <mutex>

//Headers
#include "render.h"
#include "inputhandler.h"

int main()
{
    Render render;
    InputHandler inputHandler;
    std::mutex mtx;

    const int width = 1280;
    const int height = 720;
    const std::string title = "Title";

    render.Init(width, height, title, &mtx);
    
    if(render.GetWindowPtr() == nullptr)
    {
        std::cout << "Failed to initialize Renderer" << std::endl;
        system("pause");
        return -1;
    }

    if((inputHandler.Init(&render, &mtx)) == false)
    {
        std::cout << "Failed to initialize Input Handler" << std::endl;
        system("pause");
        glfwTerminate();
        return -1;
    }

    std::thread renderThread(&Render::Loop, &render); //Create render loop

    while(!glfwWindowShouldClose(render.GetWindowPtr()))
    {
        inputHandler.ProcessInputs();
        glfwPollEvents();
    }

    renderThread.join();
    glfwTerminate();

    return 0;
}