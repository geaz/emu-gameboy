#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>

#include "shader.h"
#include "font.h"

class ResourceManager
{
    public:
        static Shader LoadShader(const char* shaderName, const char* vertextPath, const char* fragmentPath);
        static Font LoadFont(const char*fontName, const char* fontPath);
        
        static int ViewportWidth;
        static int ViewportHeight;

        static std::map<std::string, Shader> Shaders;
        static std::map<std::string, Font> Fonts;
};

#endif // RESOURCEMANAGER_H