#include "inputhandler.h"

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
}

void InputHandler::EventToggleFullscreen()
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

void InputHandler::BindHoldKey(int key, KeyCallback callback)
{
    this->HoldKeyBindings[key] = callback;
}

void InputHandler::BindOneClickKey(int key, KeyCallback callback)
{
    this->OneClickKeyBindings[key] = std::make_pair(callback, false);
}

void InputHandler::EventExitApplication()
{
    glfwSetWindowShouldClose(this->window, true);
}

void InputHandler::EventToggleWireframe()
{
    this->mtx->lock();
    glfwMakeContextCurrent(this->window);

    GLint polygonMode;
    glGetIntegerv(GL_POLYGON_MODE, &polygonMode);

    if(polygonMode == GL_LINE)
    {
        std::cout << "Polygon mode: FILL" << std::endl;
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else
    {
        std::cout << "Polygon mode: LINE" << std::endl;
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    glfwMakeContextCurrent(NULL);
    this->mtx->unlock();
}

bool InputHandler::Init(Render* render, std::mutex* _mtx)
{
    this->window = render->GetWindowPtr();

    if(this->window == nullptr) { return false; }

    this->mtx = _mtx;

    if(this->mtx == nullptr) { return false; }

    this->BindOneClickKey(GLFW_KEY_F10, [this]{ this->render->test(); });
    this->BindOneClickKey(GLFW_KEY_F11, [this]{ this->EventToggleFullscreen(); });
    this->BindOneClickKey(GLFW_KEY_F12, [this]{ this->EventToggleWireframe(); });

    this->BindHoldKey(GLFW_KEY_ESCAPE, [this]{this->EventExitApplication(); });

    return true;
}

void InputHandler::ProcessInputs()
{
    for (auto it = this->HoldKeyBindings.begin(); it != this->HoldKeyBindings.end(); ++it) {
        if(glfwGetKey(this->window, it->first) == GLFW_PRESS)
        {
            it->second();
        }
    }

    for (auto it = this->OneClickKeyBindings.begin(); it != this->OneClickKeyBindings.end(); ++it) {
        
        bool& isPressed = it->second.second;

        if(glfwGetKey(this->window, it->first) == GLFW_PRESS && !isPressed)
        {
            isPressed = true;
            it->second.first();
        }
        else if(glfwGetKey(this->window, it->first) == GLFW_RELEASE && isPressed)
        {
            isPressed = false;
        }
    }   
}