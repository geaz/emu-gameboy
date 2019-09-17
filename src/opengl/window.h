#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "structs.h"
#include "screen.h"

class Window
{
    public:        
        Window(char* title, const int width, const int height);
        
        void setClearColor(const GLfloat red, const GLfloat green, const GLfloat blue, const GLfloat alpha) const;
        void startLoop();

        void addScreen(Screen* screen);

        static Window* windowPointer;

    private:
        void handleKeys(const int key, const int scancode, const int action, const int mods) const;

        char* title;
        GLFWwindow* window;
        std::vector<Screen*> screenVec;
};

#endif // WINDOW_H