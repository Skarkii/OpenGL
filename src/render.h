#ifndef RENDER_H
#define RENDER_H

#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"

#include "ebo.h"
#include "vao.h"
#include "vbo.h"
#include "shader.h"
#include "shaderProgram.h"

#include <iostream>
#include <mutex>
#include <math.h>

class Render
{
    public:
        Render();
        ~Render();
        void Init(int width, int height, std::string title, std::mutex* _mtx);
        void Loop();
        void test();
        GLFWwindow* GetWindowPtr();
        void SetWindowPtr(GLFWwindow* win);
    private:
        std::mutex* mtx;
        GLFWwindow* window = nullptr;
        void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
        static void StaticFramebufferSizeCallback(GLFWwindow* window, int width, int height);
};


#endif // RENDER_H