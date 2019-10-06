#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "screen.h"

namespace OpenGL
{    
    class Window
    {
        public:        
            Window(std::string title, const int width, const int height);
            
            void startLoop();
            void addScreen(Screen* screen);
            void setClearColor(const GLfloat red, const GLfloat green, const GLfloat blue, const GLfloat alpha) const;

        private:
            void handleKeys(const int key, const int scancode, const int action, const int mods) const;

            GLFWwindow* glfwWindow;
            std::vector<Screen*> screenVec;
    };
    
    // Window Pointer for OpenGL callbacks
    extern Window* WindowPointer;
}

#endif // WINDOW_H