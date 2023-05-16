#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <iostream>
#include <map>
#include <functional>
#include <mutex>
#include "render.h"

typedef std::function<void()> KeyCallback;

class InputHandler
{
    public:
        InputHandler();
        ~InputHandler();
        bool Init(Render* render, std::mutex* _mtx);
        void ProcessInputs();
        void BindHoldKey(int key, KeyCallback callback);
        void BindOneClickKey(int key, KeyCallback callback);
        void HandleKeyPress(int key);
    private:   
        Render* render;
        GLFWwindow* window;
        std::mutex* mtx;
        void EventToggleFullscreen();
        void EventExitApplication();
        void EventToggleWireframe();

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        std::map<int, std::pair<KeyCallback, bool>> OneClickKeyBindings;
        std::map<int, KeyCallback> HoldKeyBindings;
};

#endif //INPUTHANDLER_H