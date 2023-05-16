#ifndef RENDER_H
#define RENDER_H

#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"

#include "ebo.h"
#include "vao.h"
#include "vbo.h"
#include "shader.h"
#include "shaderProgram.h"
#include "texture.h"

#include <iostream>
#include <mutex>
#include <math.h>
#include "include/glm/gtx/string_cast.hpp"

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
        void UpdateCameraPosition(glm::vec3 add);
        
    private:
        std::mutex* mtx;
        glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, -5.0f); 
        GLFWwindow* window = nullptr;
        float cameraSpeed = 6.0f;
        void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
        static void StaticFramebufferSizeCallback(GLFWwindow* window, int width, int height);
};


#endif // RENDER_H